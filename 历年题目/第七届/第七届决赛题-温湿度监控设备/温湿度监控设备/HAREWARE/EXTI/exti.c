/*******************************************************************************  
* �ļ���   : exti.c
* ����     : �ⲿ�ж��������� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2017/02/08
* ����     ��wevsmy
*******************************************************************************/
#include "exti.h"
#include "key.h"
#include "delay.h"
#include "led.h"
#include"beep.h"

//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�ж���Ҫʹ��AFIOʱ��
	KEY_Init();	//������ʼ��
	//B1 PA0-EXTI0  PA0�˿��ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

	EXTI_InitStrue.EXTI_Line=EXTI_Line0;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI0_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//�����ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStrue);
	//B2 PA8-EXTI8  PA8�˿��ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);

	EXTI_InitStrue.EXTI_Line=EXTI_Line8;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI9_5_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//�����ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStrue);
	//B3 PB1-EXTI1  PB1�˿��ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

	EXTI_InitStrue.EXTI_Line=EXTI_Line1;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI1_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//�����ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStrue);
	//B4 PB2-EXTI2  PB2�˿��ж��߼��жϳ�ʼ������
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2);

	EXTI_InitStrue.EXTI_Line=EXTI_Line2;
	EXTI_InitStrue.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStrue.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
	EXTI_InitStrue.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStrue);

	NVIC_InitStrue.NVIC_IRQChannel=EXTI2_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=2;//�����ȼ�2
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStrue);
}

void EXTI0_IRQHandler(void)
{
	delay_ms(30);
	if(KEY1==0)
	{		
		BEEP=!BEEP; 
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//�����Ӧ��·�ϵ��жϱ�־λ	
}
void EXTI9_5_IRQHandler(void)
{
	delay_ms(30);
	if(KEY2==0)
	{		
		LED_LE=1;//��LEDʹ�ܶ� 
		LED5=!LED5;
		LED6=!LED6;
		LED_LE=0;//�ر�LEDʹ�ܶ�   
	}
	EXTI_ClearITPendingBit(EXTI_Line8);//�����Ӧ��·�ϵ��жϱ�־λ		
}
void EXTI1_IRQHandler(void)
{
	delay_ms(30);
	if(KEY3==0)
	{		
		LED_LE=1;//��LEDʹ�ܶ� 
		LED7=!LED7;
		LED8=!LED8;
		LED_LE=0;//�ر�LEDʹ�ܶ�  
	}
	EXTI_ClearITPendingBit(EXTI_Line1);//�����Ӧ��·�ϵ��жϱ�־λ		
}
void EXTI2_IRQHandler(void)
{
	delay_ms(30);
	if(KEY4==0)
	{		
		LED_LE=1;//��LEDʹ�ܶ�  
		LED5=!LED5;
		LED6=!LED6;
		LED7=!LED7;
		LED8=!LED8;
		LED_LE=0;//�ر�LEDʹ�ܶ� 
	}
	EXTI_ClearITPendingBit(EXTI_Line2);//�����Ӧ��·�ϵ��жϱ�־λ		
}

