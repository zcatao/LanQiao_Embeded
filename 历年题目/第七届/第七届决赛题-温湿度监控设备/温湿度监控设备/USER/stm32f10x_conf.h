/**
  ******************************************************************************
  * @file    CAN/Networking/stm32f10x_conf.h 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_CONF_H
#define __STM32F10x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
 #include "stm32f10x_adc.h"
/* 模拟/数字转化器 (adc) */

 #include "stm32f10x_bkp.h"
/* 备份寄存器 (bkp) */

 #include "stm32f10x_can.h"
/* 控制器局域网 (can) */

 #include "stm32f10x_cec.h"
/* cec网络模块 (cec) */

 #include "stm32f10x_crc.h"
/* crc计算单元 (crc) */

 #include "stm32f10x_dac.h"
/* 数字/模拟转换器 (dac) */

 #include "stm32f10x_dbgmcu.h"
/* 调试支持 (dbgmcu) */

 #include "stm32f10x_dma.h"
/* 直接内存存取控制器 (dma) */

 #include "stm32f10x_exti.h"
/* 外部中断/事件控制器 (exti) */

 #include "stm32f10x_flash.h"
/* FLASH存储器 (flash) */

 #include "stm32f10x_fsmc.h"
/* 灵活的静态存储器控制器 (fsmc) */

 #include "stm32f10x_gpio.h"
/* 通用输入/输出 (gpio) */

 #include "stm32f10x_i2c.h"
/* 内部集成电路 (i2c) */

 #include "stm32f10x_iwdg.h"
/* 独立看门狗 (iwdg) */

 #include "stm32f10x_pwr.h"
/* 功耗控制 (pwr) */

 #include "stm32f10x_rcc.h"
/* 复位和时钟设置 (rcc) */

 #include "stm32f10x_rtc.h"
/* 实时时钟 (rtc) */

 #include "stm32f10x_sdio.h"
/* SDIO接口 (sdio) */

 #include "stm32f10x_spi.h"
/* 串行外设接口 (spi) */

 #include "stm32f10x_tim.h"
/* 通用定时器 (tim) */

 #include "stm32f10x_usart.h"
/* 通用同步异步收发器 (usart) */

 #include "stm32f10x_wwdg.h"
/* 窗口看门狗 (wwdg) */

 #include "misc.h" 
/* High level functions for NVIC and SysTick (add-on to CMSIS functions) */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM32F10x_CONF_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
