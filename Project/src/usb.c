/*
 * =====================================================================================
 *
 *       Filename:  usb.c
 *
 *    Description:  usb相关操作封装
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
#include "usb.h"
#include "usb_lib.h"
#include "usbcommon.h"

void USBDevice_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_GPIOClockCmd(USB_Port, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = USB_Det;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         /* 下拉输入 */
    GPIO_Init(USB_Port, &GPIO_InitStructure);

    USBCommon_Init();
}

bool USBDevice_PlugIn()
{
    // return false;///////////////////
    bool plugin = GPIO_ReadInputDataBit(USB_Port, USB_Det);
    return plugin;
}

void USBDevice_Connect()
{
    DBG_MSG("called", 0);
    USB_Init();
}

void USBDevice_Disconnect()
{
    DBG_MSG("called", 0);
    // USB_Interrupts_Config(DISABLE);
    USB_Cable_Config(DISABLE);
}