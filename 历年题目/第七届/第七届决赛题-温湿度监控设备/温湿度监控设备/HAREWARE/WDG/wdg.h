/*******************************************************************************  
* 文件名   : wdg.h
* 描述     : 看门狗驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/02/09
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __WDG_H_
#define __WDG_H_
#include "sys.h"
//独立看门狗
void IWDG_Init(u8 prer,u16 rlr); //独立看门狗初始化
void IWDG_Feed(void);//喂狗
//窗口看门狗 
void WWDG_Init(u8 tr,u8 wr,u32 fprer); //窗口看门狗初始化
void WWDG_Set_Counter(u8 cnt);//重设置WWDG计数器的值
void WWDG_NVIC_Init(void);//WWDG中断服务初始化程序

#endif
