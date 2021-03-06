/*
 * =====================================================================================
 *
 *       Filename:  hardwareDef.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2013/1/18 10:28:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  madcc (good lucky), madcc09@163.com
 *                  zhangyuxiang
 *   Organization:
 *
 * =====================================================================================
 */
#ifndef __HARDWARE_DEF__HH__
#define __HARDWARE_DEF__HH__

#define Debug_USART USART2
#define Debug_BaudRate 115200

#define Pickup_Pin GPIO_Pin_7
#define Pickup_Port GPIOB
#define Pump_Pin GPIO_Pin_15
#define Pump_Port GPIOA

#define RE_X_TIM     TIM2
#define RE_X_TIM_IRQ TIM2_IRQn
#define RE_X_PORT    GPIOA
#define RE_X_PINS    (GPIO_Pin_0|GPIO_Pin_1)

#define RE_Y_TIM     TIM3
#define RE_Y_TIM_IRQ TIM3_IRQn
#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || defined (STM32F10X_XL) || defined (STM32F10X_CL)
#define RE_Y_PORT    GPIOA
#define RE_Y_PINS    (GPIO_Pin_6|GPIO_Pin_7)
#else
#define RE_Y_PORT    GPIOB
#define RE_Y_PINS    (GPIO_Pin_4|GPIO_Pin_5)
#endif

#define X_Axis_Start_Pin GPIO_Pin_2
#define X_Axis_Start_Port GPIOC
#define X_Axis_Step_Pin GPIO_Pin_2
#define X_Axis_Step_Port GPIOD
#define X_Axis_Dir_Pin GPIO_Pin_3
#define X_Axis_Dir_Port GPIOC

#define Y_Axis_Start_Pin GPIO_Pin_11
#define Y_Axis_Start_Port GPIOC
#define Y_Axis_Step_Pin GPIO_Pin_12
#define Y_Axis_Step_Port GPIOC
#define Y_Axis_Dir_Pin GPIO_Pin_10
#define Y_Axis_Dir_Port GPIOC

#define Z_Axis_Start_Pin GPIO_Pin_4
#define Z_Axis_Start_Port GPIOC
#define Z_Axis_Step_Pin GPIO_Pin_5
#define Z_Axis_Step_Port GPIOC
#define Z_Axis_Dir_Pin GPIO_Pin_1
#define Z_Axis_Dir_Port GPIOB

#define A_Axis_Start_Pin GPIO_Pin_6
#define A_Axis_Start_Port GPIOC
#define A_Axis_Step_Pin GPIO_Pin_9
#define A_Axis_Step_Port GPIOC
#define A_Axis_Dir_Pin GPIO_Pin_8
#define A_Axis_Dir_Port GPIOC

#define X_Axis 0
#define Y_Axis 1
#define Z_Axis 2
#define A_Axis 3

#define X_Axis_Min_Port GPIOB
#define X_Axis_Min_Pin GPIO_Pin_13
#define Y_Axis_Min_Port GPIOB
#define Y_Axis_Min_Pin GPIO_Pin_14
#define Z_Axis_Min_Port GPIOB
#define Z_Axis_Min_Pin GPIO_Pin_15

#define LED_Port GPIOA
#define LED_1 GPIO_Pin_5

#define USB_Port GPIOB
#define USB_Det  GPIO_Pin_12
#define USB_DISCONNECT GPIOB
#define USB_DISCONNECT_PIN GPIO_Pin_14

#define SD_DETECT_PIN                    GPIO_Pin_7
#define SD_DETECT_GPIO_PORT              GPIOC
#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOC
#endif
