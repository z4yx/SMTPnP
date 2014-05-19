#ifndef __TOOLHEAD__H__
#define __TOOLHEAD__H__

void Toolhead_Init(void);
bool Toolhead_isReady(void);
bool Toolhead_Rotate(int16_t degree);
bool Toolhead_Z_Relative(int steps);
bool Toolhead_Z_Absolute(int steps);
bool Toolhead_Z_SetCurrentPos(int pos);
void Toolhead_GetZPos(int *z);

void Toolhead_Axis_Eneded(uint8_t axis);


#endif