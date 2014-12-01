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

#define Debug_USART USART1
#define Debug_BaudRate 115200
#define BT_USART USART3
#define BT_BaudRate 9600

#define Pickup_Pin GPIO_Pin_1
#define Pickup_Port GPIOA

/*Defined by PWM*/
// #define Ex1Heat_Pin GPIO_Pin_0
// #define HBP_Pin GPIO_Pin_1
// #define HBP_Port GPIOA

#define X_Axis_Start_Pin GPIO_Pin_6
#define X_Axis_Start_Port GPIOA
#define X_Axis_OE_Pin GPIO_Pin_7
#define X_Axis_OE_Port GPIOA
#define X_Axis_Step_Pin GPIO_Pin_5
#define X_Axis_Step_Port GPIOC
#define X_Axis_Dir_Pin GPIO_Pin_4
#define X_Axis_Dir_Port GPIOC

#define Y_Axis_Start_Pin GPIO_Pin_2
#define Y_Axis_Start_Port GPIOA
#define Y_Axis_OE_Pin GPIO_Pin_3
#define Y_Axis_OE_Port GPIOA
#define Y_Axis_Step_Pin GPIO_Pin_5
#define Y_Axis_Step_Port GPIOA
#define Y_Axis_Dir_Pin GPIO_Pin_4
#define Y_Axis_Dir_Port GPIOA

#define Z_Axis_Start_Pin GPIO_Pin_13
#define Z_Axis_Start_Port GPIOC
#define Z_Axis_OE_Pin GPIO_Pin_14
#define Z_Axis_OE_Port GPIOC
#define Z_Axis_Step_Pin GPIO_Pin_3
#define Z_Axis_Step_Port GPIOC
#define Z_Axis_Dir_Pin GPIO_Pin_2
#define Z_Axis_Dir_Port GPIOC

#define A_Axis_Start_Pin GPIO_Pin_0
#define A_Axis_Start_Port GPIOB
#define A_Axis_OE_Pin GPIO_Pin_1
#define A_Axis_OE_Port GPIOB
#define A_Axis_Step_Pin GPIO_Pin_13
#define A_Axis_Step_Port GPIOB
#define A_Axis_Dir_Pin GPIO_Pin_12
#define A_Axis_Dir_Port GPIOB

#define X_Axis 0
#define Y_Axis 1
#define Z_Axis 2
#define A_Axis 3

#define X_Axis_Min_Port GPIOB
#define X_Axis_Min_Pin GPIO_Pin_14
#define Y_Axis_Min_Port GPIOB
#define Y_Axis_Min_Pin GPIO_Pin_15
#define Z_Axis_Min_Port GPIOC
#define Z_Axis_Min_Pin GPIO_Pin_6

#define LED_Port GPIOB
#define LED_1 GPIO_Pin_8
#define LED_2 GPIO_Pin_9

#define USB_Port GPIOB
#define USB_Det  GPIO_Pin_13
#define RCC_APB2Periph_GPIO_DISCONNECT RCC_APB2Periph_GPIOB
#define USB_DISCONNECT GPIOB
#define USB_DISCONNECT_PIN GPIO_Pin_14

#define SD_DETECT_PIN                    GPIO_Pin_7
#define SD_DETECT_GPIO_PORT              GPIOC
#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOC
#endif
