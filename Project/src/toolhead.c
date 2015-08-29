/*
 * =====================================================================================
 *
 *       Filename:  toolhead.c
 *
 *    Description:  贴片头控制
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
#include "motor.h"
#include "toolhead.h"
#include "systick.h"
#include "move.h"
#include "limitSwitch.h"
#include <stdlib.h>

//当前电机旋转角度,单位为步进数
static int currentPos;

//Z轴和旋转轴是否处于运动状态
static volatile bool ZRunning, RotaterRunning, ZReseting;

void Toolhead_Init()
{
	// Motor_Init();
	currentPos = 0;
	ZRunning = RotaterRunning = false;
	ZReseting = false;
}

//步进运动完成,由电机中断调用
void Toolhead_Axis_Eneded(uint8_t axis)
{
	DBG_MSG("Axis %d done", axis);
	if(axis == Z_Axis)
		ZRunning = false;
	else if(axis == A_Axis)
		RotaterRunning = false;
}

bool Toolhead_isReady()
{
	return !ZRunning && !RotaterRunning;
}

bool Toolhead_Z_Reset()
{
	if(ZRunning)
		return false;
	ZRunning = true;
	ZReseting = true;
	if(LimitSwitch_Pressed(LimitSwitch_ZMin)){
		Motor_Start(Z_Axis, -1, Move_Dir_Back, Z_PULSE_FREQ);
	}else{
		Motor_Start(Z_Axis, -1, Move_Dir_Forward, Z_PULSE_FREQ);
	}
	return true;
}

bool Toolhead_Rotate(int16_t degree)
{
	if(RotaterRunning)
		return false;

	int d = A_PULSES_PER_CYCLE;
	d = d * degree / 360;
	RotaterRunning = true;
	Motor_Start(A_Axis, abs(d), (d > 0 ? Move_Dir_Forward : Move_Dir_Back), A_PULSE_FREQ);

	return true;
}

//贴片头Z方向相对移动
bool Toolhead_Z_Relative(int steps)
{

	if(ZRunning)
		return false;

	currentPos += steps;

	if(steps){
		ZRunning = true;
		Motor_Start(Z_Axis, abs(steps), (steps > 0 ? Move_Dir_Forward : Move_Dir_Back), Z_PULSE_FREQ);
	}

	return true;
}

//贴片头Z方向绝对移动
bool Toolhead_Z_Absolute(int steps)
{

	return Toolhead_Z_Relative(steps - currentPos);
}

bool Toolhead_Z_SetCurrentPos(int pos)
{
	currentPos = pos;
	
	return true;
}

void Toolhead_GetZPos(int *z)
{
	*z = currentPos;
}

void Toolhead_Z_limit_trigger()
{
	if(ZReseting){
		Motor_Stop(Z_Axis);
		currentPos = 0;
		ZReseting = false;
		ZRunning = false;
		DBG_MSG("Z reset done");
	}
}

