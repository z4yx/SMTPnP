/*
 * =====================================================================================
 *
 *       Filename:  command.c
 *
 *    Description:  整机状态控制
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
#include "command.h"
#include "move.h"
#include "motor.h"
#include "usb.h"
#include "toolhead.h"
#include "hostctrl.h"

//机器当前状态
static uint16_t currentState;

void Command_Init(void)
{
	currentState = MACH_STATE_OFF;
}

void Command_GetState(uint16_t *state)
{
	*state = currentState;
}

void Command_Task(void)
{
	switch(currentState) {
		case MACH_STATE_OFF:
			//检查USB连接情况
			if(USBDevice_PlugIn()){
				DBG_MSG("Try to connect USB host...", 0);
				USBDevice_Connect();
				currentState = MACH_STATE_NORMAL;
			}
			break;
		case MACH_STATE_NORMAL:
			//正常状态,等待上位机指令
			//如果USB断开,则切换至停止状态
			if(!USBDevice_PlugIn()){
				DBG_MSG("Disconnect USB host", 0);
				USBDevice_Disconnect();
				currentState = MACH_STATE_OFF;
			}
			break;
		case MACH_STATE_HOMING:
			if(Move_XY_Ready()){
				DBG_MSG("Operation \"Homing\" Done!", 0);
				currentState = MACH_STATE_NORMAL;
				Motor_PowerOff();
			}
			break;
		case MACH_STATE_MANUAL:

			break;
		case MACH_STATE_XY_MOVE:
			if(Move_XY_Ready()){
				currentState = MACH_STATE_NORMAL;
				HostCtrl_ReportOpDone("move");
				HostCtrl_ReportCoordinate();
			}
			break;
		case MACH_STATE_TOOLHEAD_ROTATE:
			if(Toolhead_isReady()){
				currentState = MACH_STATE_NORMAL;
				HostCtrl_ReportOpDone("toolhead");
				HostCtrl_ReportCoordinate();
			}
			break;
		case MACH_STATE_TOOLHEAD_Z:
			if(Toolhead_isReady()){
				currentState = MACH_STATE_NORMAL;
				HostCtrl_ReportOpDone("toolhead");
				HostCtrl_ReportCoordinate();
			}
			break;
	}
}

bool Command_StartHomingXY()
{
	if(currentState != MACH_STATE_NORMAL)
		return false;
	Motor_PowerOn();
	Move_Home(X_Axis);
	Move_Home(Y_Axis);
	currentState = MACH_STATE_HOMING;
	return true;
}

bool Command_AbsoluteMove(int xy[2], int feedrate)
{
	if(currentState != MACH_STATE_NORMAL)
		return false;
	Motor_PowerOn();
	currentState = MACH_STATE_XY_MOVE;
	return Move_AbsoluteMove(xy, feedrate);
}

bool Command_RelativeMove(int xy[2], int feedrate)
{
	if(currentState != MACH_STATE_NORMAL)
		return false;
	Motor_PowerOn();
	currentState = MACH_STATE_XY_MOVE;
	return Command_RelativeMove(xy, feedrate);
}

bool Command_Toolhead_Z_Absolute(int steps)
{
	if(currentState != MACH_STATE_NORMAL)
		return false;
	Motor_PowerOn();
	currentState = MACH_STATE_TOOLHEAD_Z;
	return Toolhead_Z_Absolute(steps);
}

bool Command_Toolhead_Rotate(int16_t degree)
{
	if(currentState != MACH_STATE_NORMAL)
		return false;
	Motor_PowerOn();
	currentState = MACH_STATE_TOOLHEAD_ROTATE;
	return Toolhead_Rotate(degree);
}

