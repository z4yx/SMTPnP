/*
 * =====================================================================================
 *
 *       Filename:  hostctrl.c
 *
 *    Description:  上位机控制请求处理
 *
 *        Version:  
 *        Created:  
 *       Revision:  
 *       Compiler:  
 *
 *         Author:  zhangyuxiang
 *   Organization:  
 *
 * =====================================================================================
 */

#include "common.h"
#include "systick.h"
#include "hostctrl.h"
#include "led.h"
#include "command.h"
#include "move.h"
#include "vacuum.h"
#include "toolhead.h"
#include "usbcdc_io.h"
#include <string.h>
#include <stdlib.h>

#define CMD_BUF_LEN 8
#define PARAM_BUF_LEN 64

enum {PARSE_INITIAL, PARSE_CMD, PARSE_PARAM};
static uint8_t parse_stage;
static bool cmd_received;
static char cmd_buf[CMD_BUF_LEN], param_buf[PARAM_BUF_LEN];

#define REPORT(info_type, format, ...) USB_CDC_printf("!I#%s#" format "\r\n", info_type, __VA_ARGS__)

void HostCtrl_Init()
{
	// USART_RxInt_Config(true);
	parse_stage = PARSE_INITIAL;
	cmd_received = false;
}

bool HostCtrl_GetCmd(char **p_cmd, char **p_param)
{
	if(cmd_received){
		*p_param = param_buf;
		*p_cmd = cmd_buf;
	}
	return cmd_received;
}

//指令已经处理完,准备接收下一指令
void HostCtrl_CmdProcessed()
{
	cmd_received = false;
}

static void parse_host_cmd(uint8_t byte)
{
	static int cmd_buf_i = 0, param_buf_i = 0;
	switch(parse_stage){
		case PARSE_INITIAL:
			//如果有尚未处理的指令,则丢弃本次指令
			if(byte == '!' && !cmd_received){
				parse_stage = PARSE_CMD;
				cmd_buf_i = param_buf_i = 0;
			}
			break;
		case PARSE_CMD:
			if('A'<=byte && byte<='Z'){
				if(cmd_buf_i < CMD_BUF_LEN-2)
					cmd_buf[cmd_buf_i++] = byte;
			}else if('#' == byte){
				cmd_buf[cmd_buf_i] = '\0';
				// cmd_received = true;
				parse_stage = PARSE_PARAM;
			}else{
				//无效指令
				parse_stage = PARSE_INITIAL;
			}
			break;
		case PARSE_PARAM:
			if('\r' == byte || '\n' == byte){
				param_buf[param_buf_i] = '\0';
				cmd_received = true;
				parse_stage = PARSE_INITIAL;
			}else{
				if(param_buf_i < PARAM_BUF_LEN-2)
					param_buf[param_buf_i++] = byte;
			}
			break;
	}
}

void HostCtrl_ReportCoordinate()
{
	int x,y,z;
	Move_GetPos(&x, &y);
	Toolhead_GetZPos(&z);
	REPORT(INFO_COORD, "X=%d Y=%d Z=%d", x, y, z);
}

void HostCtrl_ReportOpDone(const char *name)
{
	REPORT(INFO_DONE, "%s", name);
}

static void reportState()
{
	uint16_t state;

	Command_GetState(&state);
	REPORT(INFO_PRINT, "%d", (int)state);

}

//处理上位机请求
static void processRequest(char* cmd, char* param)
{
	DBG_MSG("Cmd: %s, Param: %s", cmd, param);
	if(strcmp(cmd, "QRY") == 0){
		reportState();
	}/*else if(strcmp(cmd, "STOP") == 0){
		bool ret = Command_StopPrinting();
		REPORT(INFO_REPLY, "%d", ret);
	}else if(strcmp(cmd, "LIST") == 0){
		files = FileManager_ListGFiles();
		if(files != NULL){
			for(int i=0; i<SD_MAX_ITEMS; i++){
				if(!(*files)[i][0])
					break;
				REPORT(INFO_LIST_FILES, "%s", (*files)[i]);
			}
		}
	}else if(strcmp(cmd, "START") == 0){
		int num = atoi(param);
		if(num >= 0 && num < SD_MAX_ITEMS){
			bool ret = Command_StartPrinting((*files)[num]);
			REPORT(INFO_REPLY, "%d", ret);
		}
	}*/else if(strcmp(cmd, "DBG") == 0){
		uint8_t tmp;
		int val[2] = {0};
		int result = 1;
		switch(*param){
			case 'X':
			case 'Y':
				tmp = *param-'X';
				val[tmp] = atoi(param+1);
				result = Command_RelativeMove(val, DEFAULT_FEEDRATE);
				break;
			case 'Z':
				result = Command_Toolhead_Z_Absolute(atoi(param+1));
				break;
			case 'A':
				result = Command_Toolhead_Rotate(atoi(param+1));
				break;
			case 'f':
				Vacuum_Pick(*(param+1) == '1');
				result = true;
				break;
			case 'v':
				Vacuum_Pump_On(*(param+1) == '1');
				result = true;
				break;
		}
		REPORT(INFO_REPLY, "%d", result);
	}else if(strcmp(cmd, "ABSXY") == 0){
		char *sep = strchr(param, ',');
		if(sep){
			int xy[2];
			xy[0] = atoi(param);
			xy[1] = atoi(sep+1);
			DBG_MSG("Absolute Move %d,%d", xy[0], xy[1]);
			Command_AbsoluteMove(xy, DEFAULT_FEEDRATE);
		}
	}else if(strcmp(cmd, "ABSZ") == 0){
		int z = atoi(param);
		DBG_MSG("Absolute Z Move steps:%d", z);
		Command_Toolhead_Z_Absolute(z);
	}else if(strcmp(cmd, "ROTATE") == 0){
		int z = atoi(param);
		DBG_MSG("Rotate degree:%d", z);
		Command_Toolhead_Rotate(z);
	}else if(strcmp(cmd, "SETC") == 0){
		char *sep = strchr(param, ',');
		if(sep){
			int xy[2];
			xy[0] = atoi(param);
			xy[1] = atoi(sep+1);
			DBG_MSG("Set Position %d,%d", xy[0], xy[1]);
			Move_SetCurrentPos(xy);
		}
	}else if(strcmp(cmd, "GETC") == 0){
		HostCtrl_ReportCoordinate();
	}else if(strcmp(cmd, "HOMEXY") == 0){
		Command_StartHomingXY();
	}else if(strcmp(cmd, "HOMEZ") == 0){
		Command_StartHomingZ();
	}
}

static void fetchHostCmd(void)
{
	static SysTick_t last_report = 0;
	static uint8_t led_state = LED_ON;

	char *p_cmd, *p_param;
	SysTick_t now = GetSystemTick();
	if(now - last_report > REPORT_PERIOD){

		last_report = now;

		LED_Enable(LED1, led_state);
		led_state = (led_state == LED_ON ? LED_OFF : LED_ON);

	}

    __disable_irq();

	if(HostCtrl_GetCmd(&p_cmd, &p_param)){
		processRequest(p_cmd, p_param);
		HostCtrl_CmdProcessed();
	}
    __enable_irq();
}

void HostCtrl_Task(void)
{
	fetchHostCmd();
}

void HostCtrl_Recv_Interrupt(uint8_t byte)
{
	parse_host_cmd(byte);
}
