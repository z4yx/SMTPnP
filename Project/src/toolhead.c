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

//当前电机旋转角度,单位为步进数
static int currentPos;

//Z轴和旋转轴是否处于运动状态
static volatile bool ZRunning, RotaterRunning;

void Toolhead_Init()
{
	// Motor_Init();
	currentPos = 0;
	ZRunning = RotaterRunning = false;
}

//步进运动完成,由电机中断调用
void Toolhead_Axis_Eneded(uint8_t axis)
{
	if(axis == Z_Axis)
		ZRunning = false;
	else if(axis == A_Axis)
		RotaterRunning = false;
}

bool Toolhead_isReady()
{
	return !ZRunning && !RotaterRunning;
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
	int tmp;

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
