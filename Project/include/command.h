#ifndef __COMMAND__H__
#define __COMMAND__H__

enum { MACH_STATE_OFF, MACH_STATE_NORMAL, MACH_STATE_HOMING, MACH_STATE_MANUAL,
    MACH_STATE_XY_MOVE, MACH_STATE_TOOLHEAD_ROTATE, MACH_STATE_TOOLHEAD_Z,
    MACH_STATE_Z_RESET
};

void Command_Init(void);
void Command_GetState(uint16_t *state);
bool Command_StartHomingXY();
bool Command_StartHomingZ();
bool Command_RelativeMove(int xy[2], int feedrate);
bool Command_AbsoluteMove(int xy[2], int feedrate);
bool Command_Toolhead_Rotate(int16_t degree);
bool Command_Toolhead_Z_Absolute(int steps);

#endif /* __COMMAND__H__ */