#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"

void USART_Config(void);
int USART_putchar(int ch);
int USART_getchar(void);
void USART_printf(char *Data, ...);

#endif
