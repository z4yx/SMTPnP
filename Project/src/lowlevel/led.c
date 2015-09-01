/*
 * =====================================================================================
 *
 *       Filename:  led.c
 *
 *    Description:  实现板载LED的控制
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
#include "led.h"

void LED_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_GPIOClockCmd(LED_Port, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
#ifdef IS_GPIO_OTYPE 
    //New GPIO peripheral
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
#else
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
#endif
    GPIO_Init(LED_Port, &GPIO_InitStructure);

    GPIO_SetBits(LED_Port, LED_1);
}

void LED_Enable(int LEDx, bool bEnabled)
{
    if (!bEnabled)
        GPIO_ResetBits(LED_Port, LED_1);
    else
        GPIO_SetBits(LED_Port, LED_1);
}
