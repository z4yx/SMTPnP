/*
 * =====================================================================================
 *
 *       Filename:  move.c
 *
 *    Description:  XY轴运动控制
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
#include "move.h"
#include "systick.h"
#include "limitSwitch.h"
#include <stdlib.h>

#define MIN2SEC 60

//当前位置(相对原点的距离,单位um),及挤出器累计旋转量
static int currentPos[2];

//当前位置(以电机的步进数量为单位)
static int currentSteps[2];

//步进电机每个脉冲产生的位移
static float um_per_pulse[2];

//三轴当前状态
static volatile uint8_t currentState[2];

static const int8_t motorDirFix[4] = {X_DIRECTION_ADJ, Y_DIRECTION_ADJ};

void Move_Init()
{
	Motor_Init();
	LimitSwitch_Config();

	um_per_pulse[X_Axis] = (float)X_DISTANCE_PER_CYCLE / X_PULSES_PER_CYCLE;
	um_per_pulse[Y_Axis] = (float)Y_DISTANCE_PER_CYCLE / Y_PULSES_PER_CYCLE;

	for (int i = 0; i < 2; ++i)
	{
		currentState[i] = Axis_State_Ready;
	}
}

void Move_GetPos(int *x, int *y)
{
	*x = currentPos[0];
	*y = currentPos[1];
}

static bool alreadyHomed(uint8_t axis)
{
	if(axis == X_Axis)
		return LimitSwitch_Pressed(LimitSwitch_XMin);
	if(axis == Y_Axis)
		return LimitSwitch_Pressed(LimitSwitch_YMin);
	return false;
}

static void homingDone(uint8_t axis)
{
	DBG_MSG("Axis %d homing Done", (int)axis);
	Motor_Stop(axis);
	currentPos[axis] = 0;
	currentSteps[axis] = 0;
	currentState[axis] = Axis_State_Ready;
}

//步进运动完成,由电机中断调用
void Move_Axis_Eneded(uint8_t axis)
{
	if(axis < 2)
		currentState[axis] = Axis_State_Ready;
	DBG_MSG("Axis %d Ended", (int)axis);
}

//三轴均处于待命状态
bool Move_XY_Ready()
{
	for (int i = 0; i < 2; ++i)
	{
		if(currentState[i] != Axis_State_Ready)
			return false;
	}
	return true;
}

//开始回原点过程
bool Move_Home(uint8_t axis)
{
	if(currentState[axis] != Axis_State_Ready) {
		ERR_MSG("Axis %d is not Ready! state = %d", (int)axis, (int)currentState[axis]);
		return false;
	}
	//回原点前先检查限位开关是否已经被按下了
	if(alreadyHomed(axis)) {
		DBG_MSG("Axis %d already homed!", (int)axis);
		homingDone(axis);
		return true;
	}

	currentState[axis] = Axis_State_Homing;
	//一直运动直到触碰限位开关
	Motor_Start(axis, -1, Move_Dir_Back * motorDirFix[axis], DEFAULT_FEEDRATE / MIN2SEC / um_per_pulse[axis]);

	return true;
}

//根据距离计算步进数量
int calc_step(int axis, int um)
{
	return um/um_per_pulse[axis];
}

//三轴相对移动及挤出器旋转
bool Move_RelativeMove(int xyza[2], int feedrate)
{
	int tmp[2];

	for (int i = 0; i < 2; ++i)
		tmp[i] = currentPos[i] + xyza[i];

	return Move_AbsoluteMove(tmp, feedrate);
}

//三轴绝对移动
bool Move_AbsoluteMove(int xyza[2], int feedrate)
{
	int tmp[2], delta[2], dir[2];

	if(!Move_XY_Ready())
		return false;

	if(xyza[X_Axis] < 0 || xyza[X_Axis] > X_MAX_LIMIT)
		return false;
	if(xyza[Y_Axis] < 0 || xyza[Y_Axis] > Y_MAX_LIMIT)
		return false;

	for (int i = 0; i < 2; ++i){
		int step = calc_step(i, xyza[i]);
		int d = step - currentSteps[i];
		DBG_MSG("axis %d step %d", i, d);

		dir[i] = motorDirFix[i] * (d > 0 ? Move_Dir_Forward : Move_Dir_Back);
		tmp[i] = abs(d);
		delta[i] = xyza[i] - currentPos[i];

		currentPos[i] = xyza[i];
		currentSteps[i] = step;
	}

	float distance = Distance2D(delta[X_Axis], delta[Y_Axis]);
	if(distance < 1) {
		distance = abs(delta[A_Axis]);
		if(distance < 1) {
			ERR_MSG("Move distance < 1", 0);
			return false;
		}
	}
	float duration = distance / feedrate * MIN2SEC;

	DBG_MSG("duration: %dms", (int)(duration*1000));

	for (int i = 0; i < 2; ++i)
	{
		if(!tmp[i])
			continue;
		currentState[i] = Axis_State_Moving;
		Motor_Start(i, tmp[i], dir[i], (uint32_t)(tmp[i]/duration));
	}

	return true;
}

bool Move_SetCurrentPos(int xyza[2])
{
	if(xyza[X_Axis] < 0 || xyza[X_Axis] > X_MAX_LIMIT)
		return false;
	if(xyza[Y_Axis] < 0 || xyza[Y_Axis] > Y_MAX_LIMIT)
		return false;


	for (int i = 0; i < 2; ++i){
		currentPos[i] = xyza[i];
		currentSteps[i] = calc_step(i, xyza[i]);
	}
	
	return true;
}

//由限位开关中断调用
void Move_LimitReached(uint8_t sw_num)
{
	bool err = false;
	uint8_t err_axis;
	switch(sw_num) {
		case LimitSwitch_XMin:
			if(currentState[X_Axis] == Axis_State_Homing)
				homingDone(X_Axis);
			else{
				err = true;
				err_axis = X_Axis;
			}
			break;

		case LimitSwitch_YMin:
			if(currentState[Y_Axis] == Axis_State_Homing)
				homingDone(Y_Axis);
			else{
				err = true;
				err_axis = Y_Axis;
			}
			break;

		// case LimitSwitch_XMax:
		// ...

	}
	if(err) {
		// Motor_Stop(err_axis);
		ERR_MSG("Limit switch on illegally! axis=%d, switch=%d", (int)err_axis, (int)sw_num);
	}
}