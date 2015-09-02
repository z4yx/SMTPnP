#include "common.h"
#include "rotary_encoder.h"
#include "systick.h"

void RotaryEnc_Config(TIM_TypeDef *TIMx, GPIO_TypeDef* Port, uint16_t Pins, uint16_t Number)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;

    RCC_GPIOClockCmd(Port, ENABLE);
    RCC_TIMClockCmd(TIMx, ENABLE);

    GPIO_InitStructure.GPIO_Pin = Pins;
#ifdef IS_GPIO_OTYPE 
    //New GPIO peripheral
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
#else
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
#endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Port, &GPIO_InitStructure);

#ifdef IS_GPIO_OTYPE //New GPIO peripheral
    for (uint16_t i = Pins; i;)
    {
        uint16_t lowbit = i&-i;
        GPIO_PinAFConfig(Port, GPIO_Pin2PinSource(lowbit), TIMtoGPIOAlternateFunction(TIMx));
        i^=lowbit;
    }
#endif

    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
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
    return TIM_GetCounter(TIMx);
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
