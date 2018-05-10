/*******************************************************************************  
* 文件名   : wkup.c
* 描述     : 待机唤醒驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/2/18
* 作者     ：wevsmy
*******************************************************************************/
#include "wkup.h"
#include "delay.h"
#include "led.h"

void Sys_Standby(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//使能PWR外设时钟
	PWR_WakeUpPinCmd(ENABLE);//使能唤醒管脚功能
	PWR_EnterSTANDBYMode();//进入待机模式
}
//系统进入待机模式
void Sys_Enter_Standby(void)
{	
	RCC_APB2PeriphResetCmd(0x01fc,DISABLE);//复位所有IO口
	Sys_Standby();
}
//检测B1脚的信号
//返回值1：连续按下2S以上
//      0: 错误触发
u8 Check_WKUP(void)
{
	u8 t=0;
	LED_LE=1;
	LED8=0;
	LED_LE=0;
	while(1)
	{
		if(WKUP_KD==0)
		{
			t++;
			delay_ms(20);
			if(t>=100)
			{
				LED_LE=1;
				LED8=0;
				LED_LE=0;
				return 1;
			}
		}
		else
		{
			LED_LE=1;
			LED8=1;
			LED_LE=0;
			return 0;	
		}
	}
}
//中断线
void EXTI0_IRQHandler(void)
{
	EXTI_GetITStatus(EXTI_Line0);
	if(Check_WKUP())
	{
		Sys_Enter_Standby();	
	}
}
//按键B1初始化
void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//外部中断方式
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//中断线0连接GPIOA.0

	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
