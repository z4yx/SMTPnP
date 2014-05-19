#ifndef __MOTOR__H__
#define __MOTOR__H__

enum { Move_Dir_Back = -1, Move_Dir_Forward = 1 };

void Motor_Stop(int motor_enum);
void Motor_Start(int motor_enum, int steps, int skip, int8_t dir);
void Motor_PowerOff(void);
void Motor_PowerOn(void);
bool Motor_isPowerOn(void);
void Motor_Init(void);

void Motor_Interrupt(void);


#endif /* __MOTOR__H__ */