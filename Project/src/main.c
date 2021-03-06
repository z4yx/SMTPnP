/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  程序入口
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
#include "usart.h"
#include "systick.h"
#include "motor.h"
#include "move.h"
#include "toolhead.h"
#include "command.h"
#include "vacuum.h"
#include "hostctrl.h"
#include "usb.h"

const Task_t SystemTasks[] = { LimitSwitch_Task, HostCtrl_Task, Command_Task};


static void periphInit()
{
	Vacuum_Config();
	Move_Init();
	Toolhead_Init();
	USBDevice_Config();
	Command_Init();
	HostCtrl_Init();
}

//核心组件初始化,包括串口(用于打印调试信息)
static void coreInit()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	SystemCoreClockUpdate();
	SysTick_Init();
	LED_Config();
	USART_Config(Debug_USART, Debug_BaudRate);
}

#ifdef STM32F411xE
static void ChangeClockConfig(void)
{
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
    while (RCC_GetSYSCLKSource() != 0x00);

	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_WaitForHSEStartUp() != SUCCESS);

	RCC_PLLCmd(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSE, HSE_VALUE/1000000, 336, 4, 7);
	RCC_PLLCmd(ENABLE);
	while((RCC->CR & RCC_CR_PLLRDY) == 0);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    while (RCC_GetSYSCLKSource() != 0x08);
}
#endif

int main(void)
{
	RCC_ClocksTypeDef clocks;
#ifdef STM32F411xE
	ChangeClockConfig();
#endif

	RCC_GetClocksFreq(&clocks);

	coreInit();

	Delay_ms(1000);

	DBG_MSG("\r\n\r\n", 0);
	DBG_MSG("SystemCoreClock: %u", SystemCoreClock);
	DBG_MSG("Clock Source: %d", RCC_GetSYSCLKSource());
	DBG_MSG("SYSCLK: %d, H: %d, P1: %d, P2: %d",
		clocks.SYSCLK_Frequency,
		clocks.HCLK_Frequency,
		clocks.PCLK1_Frequency,
		clocks.PCLK2_Frequency);

	periphInit();

	DBG_MSG("Peripheral init done.", 0);

	while (1)
	{

		//运行系统中声明的任务
		for(int i = 0; i < sizeof(SystemTasks)/sizeof(Task_t); i++)
			(SystemTasks[i])();
	}
}

#ifdef  USE_FULL_ASSERT

/**
	* @brief  Reports the name of the source file and the source line number
	*         where the assert_param error has occurred.
	* @param  file: pointer to the source file name
	* @param  line: assert_param error line source number
	* @retval None
	*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
		 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	ERR_MSG("%s:%d", file, line);

	/* Infinite loop */
	while (1)
	{
	}
}

#endif
