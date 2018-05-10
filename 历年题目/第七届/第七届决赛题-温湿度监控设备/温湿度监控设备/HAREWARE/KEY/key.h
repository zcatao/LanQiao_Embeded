/*******************************************************************************  
* 文件名   : key.h
* 描述     : key驱动 PA0-B1 PA8-B2 PB1-B3 PB2-B4  
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/12/18
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __KEY_H_
#define __KEY_H_
#include "sys.h"
#include "delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键1
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//读取按键2
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键3 
#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//读取按键4 

#define KEY1_PRES 1 
#define KEY2_PRES 2
#define KEY3_PRES 3
#define KEY4_PRES 4
 
void KEY_Init(void); //按键初始化
u8 KEY_Scan(u8 mode);
void Key_Scan(void);
#endif
