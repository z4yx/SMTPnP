/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  项目的公共函数和参数定义
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
#ifndef __COMMON__H__
#define __COMMON__H__

#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL) 
#include "stm32f10x.h"

#include "usb_type.h" //for definition of bool

#elif defined(STM32F40_41xxx) || defined(STM32F427_437xx) || defined(STM32F429_439xx) || defined(STM32F401xx) || defined(STM32F411xE) || defined(STM32F446xx)
#include "stm32f4xx.h"

typedef enum{FALSE, TRUE} bool;

#endif
#include "hardwareDef.h"
#include "configure.h"
#include <stdint.h>
#include <stdio.h>

#define true TRUE
#define false FALSE

#define DBG_MSG(format, ...) printf("[Debug]%s: " format "\r\n", __func__, ##__VA_ARGS__)
#define ERR_MSG(format, ...) printf("[Error]%s: " format "\r\n", __func__, ##__VA_ARGS__)
 
uint8_t TIMtoGPIOAlternateFunction(TIM_TypeDef* TIMx);
uint8_t GPIO_Pin2PinSource(uint16_t GPIO_Pin);
void RCC_TIMClockCmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void RCC_GPIOClockCmd(GPIO_TypeDef* GPIOx, FunctionalState state);
void RCC_USARTClockCmd(USART_TypeDef* USARTx, FunctionalState state);
void Timer_16bit_Calc(int freq, uint16_t *period, uint16_t *prescaler);
float Distance2D(float dx, float dy);

typedef void (*Task_t)(void);

//系统中所有的任务函数
void Command_Task(void);
void LimitSwitch_Task(void);
void HostCtrl_Task(void);

#endif /* __COMMON__H__ */