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
#include "common.h"

#ifdef RCC_AHB2ENR_OTGFSEN //stm32f4xx
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#else
#include "usb_lib.h"
#include "usbcommon.h"
#endif


#ifdef RCC_AHB2ENR_OTGFSEN //stm32f4xx
    #ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
      #if defined ( __ICCARM__ ) /*!< IAR Compiler */
        #pragma data_alignment=4   
      #endif
    #endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
       
    __ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;
#endif

void USBDevice_Config()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_GPIOClockCmd(USB_Port, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = USB_Det;
#ifdef IS_GPIO_OTYPE 
    //New GPIO peripheral
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
#else
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;         /* 下拉输入 */
#endif
    GPIO_Init(USB_Port, &GPIO_InitStructure);

#ifdef RCC_AHB2ENR_OTGFSEN //stm32f4xx
    USBD_Init(&USB_OTG_dev,
#ifdef USE_USB_OTG_HS 
            USB_OTG_HS_CORE_ID,
#else            
            USB_OTG_FS_CORE_ID,
#endif  
            &USR_desc, 
            &USBD_CDC_cb, 
            &USR_cb);
#else
    USBCommon_Init();
#endif
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
#ifndef RCC_AHB2ENR_OTGFSEN //stm32f4xx
    USB_Init();
#endif
}

void USBDevice_Disconnect()
{
    DBG_MSG("called", 0);
#ifndef RCC_AHB2ENR_OTGFSEN //stm32f4xx
    // USB_Interrupts_Config(DISABLE);
    USB_Cable_Config(DISABLE);
#endif
}