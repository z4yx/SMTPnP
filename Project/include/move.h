#ifndef __MOVE__H__
#define __MOVE__H__

enum { Axis_State_Ready, Axis_State_Moving, Axis_State_Homing };

void Move_Init(void);
bool Move_Home(uint8_t axis);
bool Move_isReady(void);
bool Move_RelativeMove(int xy[2]);
bool Move_AbsoluteMove(int xy[2]);
bool Move_SetCurrentPos(int xy[2]);
void Move_GetPos(int *x, int *y);

void Move_LimitReached(uint8_t sw_num);
void Move_Axis_Eneded(uint8_t axis);

#endif /* __MOVE__H__ */