#ifndef ROTARY_ENC_H
#define ROTARY_ENC_H 

#include "stm32f10x.h"

void RotaryEnc_Config(TIM_TypeDef *TIMx, GPIO_TypeDef* Port, uint16_t Pins, uint16_t Number);
void RotaryEnc_ClearCounter(TIM_TypeDef *TIMx);
uint16_t RotaryEnc_GetCounter(TIM_TypeDef *TIMx);
void RotaryEnc_TIM_SetInterrupt(TIM_TypeDef *TIMx, uint8_t Irq);

#endif
