#ifndef __HOSTCTRL_H
#define	__HOSTCTRL_H

#include "stm32f10x.h"

void HostCtrl_Init();
bool HostCtrl_GetCmd(char **p_cmd, char **p_param);
void HostCtrl_Recv_Interrupt(uint8_t byte);
void HostCtrl_CmdProcessed(void);
void HostCtrl_ReportOpDone(const char *name);
void HostCtrl_ReportCoordinate(void);

#define INFO_LIST_FILES  "LIST"
#define INFO_PRINT       "PRT"
#define INFO_REPLY       "RE"
#define INFO_DONE        "DONE"
#define INFO_COORD       "COORD"

#endif
