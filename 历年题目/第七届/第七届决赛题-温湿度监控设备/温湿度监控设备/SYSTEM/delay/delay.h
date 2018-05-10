#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"
void delay_init(void); //初始化延迟函数
void delay_ms(u16 nms);//延时nms
void delay_us(u32 nus);//延时nus

#endif





























