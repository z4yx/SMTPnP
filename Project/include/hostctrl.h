#ifndef __HOSTCTRL_H
#define	__HOSTCTRL_H

#include "stm32f10x.h"

void HostCtrl_Init(USART_TypeDef * usart);
bool HostCtrl_GetCmd(char **p_cmd, char **p_param);
void HostCtrl_Interrupt(void);
void HostCtrl_CmdProcessed(void);

#define INFO_LIST_FILES  "LIST"
#define INFO_PRINT       "PRT"
#define INFO_REPLY       "RE"
#define INFO_DONE        "DONE"
#define INFO_COORD       "COORD"

#endif
