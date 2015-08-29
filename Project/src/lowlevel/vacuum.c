/*
 * =====================================================================================
 *
 *       Filename:  vacuum.c
 *
 *    Description:  真空吸笔控制
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
#include "vacuum.h"


void Vacuum_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_GPIOClockCmd(Pickup_Port, ENABLE); 
	RCC_GPIOClockCmd(Pump_Port, ENABLE); 

	GPIO_InitStructure.GPIO_Pin =  Pickup_Pin;
#ifdef IS_GPIO_OTYPE 
    //New GPIO peripheral
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
#else
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
#endif
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(Pickup_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  Pump_Pin;

    GPIO_Init(Pump_Port, &GPIO_InitStructure);

    Vacuum_Pump_On(false);
	Vacuum_Pick(false);
}

void Vacuum_Pick(bool bEnabled)
{
#ifdef DRIVER_BOARD_POLARITY
	bEnabled = !bEnabled;
#endif

    if (bEnabled)
        GPIO_SetBits(Pickup_Port, Pickup_Pin);
    else
        GPIO_ResetBits(Pickup_Port, Pickup_Pin);
}

void Vacuum_Pump_On(bool bEnabled)
{
#ifdef DRIVER_BOARD_POLARITY
    bEnabled = !bEnabled;
#endif

    if (bEnabled)
        GPIO_SetBits(Pump_Port, Pump_Pin);
    else
        GPIO_ResetBits(Pump_Port, Pump_Pin);
}
