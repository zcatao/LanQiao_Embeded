/*******************************************************************************  
* 文件名   : led.H
* 描述     : LED驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/12/18
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __LED_H_
#define __LED_H_
#include "sys.h"
/*LED端口定义*/
#define LED_LE PDout(2)//LED使能端口 1 打开 0 关闭
//LED为 1(高电平)灭 0(低电平)亮 
#define LED1 PCout(8)
#define LED2 PCout(9)
#define LED3 PCout(10)
#define LED4 PCout(11)
#define LED5 PCout(12)
#define LED6 PCout(13)
#define LED7 PCout(14)
#define LED8 PCout(15)

void LED_Init(void); //LED初始化

#endif
