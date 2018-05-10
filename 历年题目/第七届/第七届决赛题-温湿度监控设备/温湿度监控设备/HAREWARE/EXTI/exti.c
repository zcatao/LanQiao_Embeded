/*******************************************************************************  
* 文件名   : exti.c
* 描述     : 外部中断驱动代码 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/02/08
* 作者     ：wevsmy
*******************************************************************************/
#include "exti.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include"beep.h"

//外部中断初始化函数
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断需要使能AFIO时钟
	KEY_Init();	//按键初始化
	//B1 PA0-EXTI0  PA0端口中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

	EXTI_InitStrue.EXTI_Line=EXTI_Line0;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI0_IRQn;//使能按键所在的外部中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//子优先级2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStrue);
	//B2 PA8-EXTI8  PA8端口中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);

	EXTI_InitStrue.EXTI_Line=EXTI_Line8;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI9_5_IRQn;//使能按键所在的外部中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//子优先级2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStrue);
	//B3 PB1-EXTI1  PB1端口中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

	EXTI_InitStrue.EXTI_Line=EXTI_Line1;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI1_IRQn;//使能按键所在的外部中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//子优先级2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStrue);
	//B4 PB2-EXTI2  PB2端口中断线及中断初始化配置
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);

	EXTI_InitStrue.EXTI_Line=EXTI_Line2;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI2_IRQn;//使能按键所在的外部中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//子优先级2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStrue);
}

void EXTI0_IRQHandler(void)
{
	delay_ms(30);
	if(KEY1==0)
	{		
		BEEP=!BEEP; 
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//清除对应线路上的中断标志位	
}
void EXTI9_5_IRQHandler(void)
{
	delay_ms(30);
	if(KEY2==0)
	{		
		LED_LE=1;//打开LED使能端 
		LED5=!LED5;
		LED6=!LED6;
		LED_LE=0;//关闭LED使能端   
	}
	EXTI_ClearITPendingBit(EXTI_Line8);//清除对应线路上的中断标志位		
}
void EXTI1_IRQHandler(void)
{
	delay_ms(30);
	if(KEY3==0)
	{		
		LED_LE=1;//打开LED使能端 
		LED7=!LED7;
		LED8=!LED8;
		LED_LE=0;//关闭LED使能端  
	}
	EXTI_ClearITPendingBit(EXTI_Line1);//清除对应线路上的中断标志位		
}
void EXTI2_IRQHandler(void)
{
	delay_ms(30);
	if(KEY4==0)
	{		
		LED_LE=1;//打开LED使能端  
		LED5=!LED5;
		LED6=!LED6;
		LED7=!LED7;
		LED8=!LED8;
		LED_LE=0;//关闭LED使能端 
	}
	EXTI_ClearITPendingBit(EXTI_Line2);//清除对应线路上的中断标志位		
}

