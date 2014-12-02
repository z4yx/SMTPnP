#ifndef __COMMAND__H__
#define __COMMAND__H__

enum { MACH_STATE_OFF, MACH_STATE_NORMAL, MACH_STATE_HOMING, MACH_STATE_MANUAL};

void Command_Init(void);
void Command_GetState(uint16_t *state);
void Command_StartHoming(uint8_t axis);

#endif /* __COMMAND__H__ */