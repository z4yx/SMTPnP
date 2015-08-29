/*
 * =====================================================================================
 *
 *       Filename:  common.c
 *
 *    Description:  项目的公共函数实现
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
#include <math.h>

void RCC_GPIOClockCmd(GPIO_TypeDef* GPIOx, FunctionalState state)
{
	uint32_t rcc;
#if defined (RCC_APB2Periph_GPIOA) 
	switch((uint32_t)GPIOx) {
		case (uint32_t)GPIOA:
			rcc = RCC_APB2Periph_GPIOA;
			break;
		case (uint32_t)GPIOB:
			rcc = RCC_APB2Periph_GPIOB;
			break;
		case (uint32_t)GPIOC:
			rcc = RCC_APB2Periph_GPIOC;
			break;
		case (uint32_t)GPIOD:
			rcc = RCC_APB2Periph_GPIOD;
			break;
		case (uint32_t)GPIOE:
			rcc = RCC_APB2Periph_GPIOE;
			break;
		case (uint32_t)GPIOF:
			rcc = RCC_APB2Periph_GPIOF;
			break;
		case (uint32_t)GPIOG:
			rcc = RCC_APB2Periph_GPIOG;
			break;
		default:
			/* Invalid argument! */
			return;
	}
	RCC_APB2PeriphClockCmd(rcc, state);
#elif defined (RCC_AHB1Periph_GPIOA)
	switch((uint32_t)GPIOx) {
		case (uint32_t)GPIOA:
			rcc = RCC_AHB1Periph_GPIOA;
			break;
		case (uint32_t)GPIOB:
			rcc = RCC_AHB1Periph_GPIOB;
			break;
		case (uint32_t)GPIOC:
			rcc = RCC_AHB1Periph_GPIOC;
			break;
		case (uint32_t)GPIOD:
			rcc = RCC_AHB1Periph_GPIOD;
			break;
		case (uint32_t)GPIOE:
			rcc = RCC_AHB1Periph_GPIOE;
			break;
		case (uint32_t)GPIOF:
			rcc = RCC_AHB1Periph_GPIOF;
			break;
		case (uint32_t)GPIOG:
			rcc = RCC_AHB1Periph_GPIOG;
			break;
		case (uint32_t)GPIOH:
			rcc = RCC_AHB1Periph_GPIOH;
			break;
		case (uint32_t)GPIOI:
			rcc = RCC_AHB1Periph_GPIOI;
			break;
		case (uint32_t)GPIOJ:
			rcc = RCC_AHB1Periph_GPIOJ;
			break;
		case (uint32_t)GPIOK:
			rcc = RCC_AHB1Periph_GPIOK;
			break;
		default:
			/* Invalid argument! */
			return;
	}
	RCC_AHB1PeriphClockCmd(rcc, state);
#else
	#error "RCC of GPIO is unknown"
#endif
}

void RCC_USARTClockCmd(USART_TypeDef* USARTx, FunctionalState state)
{
	switch((uint32_t)USARTx) {
		case (uint32_t)USART1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, state);
			break;
		case (uint32_t)USART2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, state);
			break;
		case (uint32_t)USART3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, state);
			break;
		default:
			/* Invalid argument! */
			return;
	}
}

void RCC_TIMClockCmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	switch((uint32_t)TIMx) {
#ifdef TIM2
		case (uint32_t)TIM2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, NewState);
			break;
#endif
#ifdef TIM3
		case (uint32_t)TIM3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, NewState);
			break;
#endif
#ifdef TIM4
		case (uint32_t)TIM4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, NewState);
			break;
#endif
#ifdef TIM5
		case (uint32_t)TIM5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, NewState);
			break;
#endif
#ifdef TIM6
		case (uint32_t)TIM6:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, NewState);
			break;
#endif
#ifdef TIM7
		case (uint32_t)TIM7:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, NewState);
			break;
#endif
#ifdef TIM12
		case (uint32_t)TIM12:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, NewState);
			break;
#endif
#ifdef TIM13
		case (uint32_t)TIM13:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, NewState);
			break;
#endif
#ifdef TIM14
		case (uint32_t)TIM14:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, NewState);
			break;
#endif
#ifdef TIM1
		case (uint32_t)TIM1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, NewState);
			break;
#endif
#ifdef TIM8
		case (uint32_t)TIM8:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, NewState);
			break;
#endif
#ifdef TIM9
		case (uint32_t)TIM9:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, NewState);
			break;
#endif
#ifdef TIM10
		case (uint32_t)TIM10:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, NewState);
			break;
#endif
#ifdef TIM11
		case (uint32_t)TIM11:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, NewState);
			break;
#endif
#ifdef TIM15
		case (uint32_t)TIM15:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, NewState);
			break;
#endif
#ifdef TIM16
		case (uint32_t)TIM16:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, NewState);
			break;
#endif
#ifdef TIM17
		case (uint32_t)TIM17:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, NewState);
			break;
#endif
		default:
			/* Invalid argument! */
			return;
	}
}

//根据频率(Hz)计算TIM的参数
void Timer_16bit_Calc(int freq, uint16_t *period, uint16_t *prescaler)
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	uint32_t tmp = RCC_Clocks.PCLK2_Frequency / freq;
	*prescaler = 1;
	while(tmp > 0xffff){
		*prescaler <<= 1;
		tmp >>= 1;
	}
	(*prescaler) --;
	*period = tmp-1;
}

float Distance2D(float dx, float dy)
{
	return sqrtf(dx*dx + dy*dy);
}
