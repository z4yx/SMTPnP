#include "rotary_encoder.h"
#include "systick.h"
#include "common.h"

void RotaryEnc_Config(TIM_TypeDef *TIMx, GPIO_TypeDef* Port, uint16_t Pins, uint16_t Number)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_GPIOClockCmd(Port, ENABLE);
    RCC_TIMClockCmd(TIMx, ENABLE);

    GPIO_InitStructure.GPIO_Pin = Pins;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Port, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
    TIM_TimeBaseStructure.TIM_Period = Number-1;  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

    TIM_EncoderInterfaceConfig(TIMx, TIM_EncoderMode_TI1, 
                            TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 7; //0111: fSAMPLING=fDTS/4, N=8
    TIM_ICInit(TIMx, &TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInit(TIMx, &TIM_ICInitStructure);

    TIM_Cmd(TIMx, ENABLE);
}

void RotaryEnc_ClearCounter(TIM_TypeDef *TIMx)
{
    TIM_SetCounter(TIMx, 0);
}

uint16_t RotaryEnc_GetCounter(TIM_TypeDef *TIMx)
{
    TIM_GetCounter(TIMx);
}

void RotaryEnc_TIM_SetInterrupt(TIM_TypeDef *TIMx, uint8_t Irq)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;   // 指定响应优先级别
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannel = Irq; //指定中断源
    NVIC_Init(&NVIC_InitStructure);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);
}
