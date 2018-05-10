/*******************************************************************************  
* �ļ���   : led.c
* ����     : LED���� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/12/18
* ����     ��wevsmy
*******************************************************************************/
#include"led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//GPIOC,GPIOD

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);//LED�˿�PC8-PC15

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOD,&GPIO_InitStructure);//LEDʹ�ܶ˿�PD2
	/*��ʼ���ر�LED*/
	GPIO_SetBits(GPIOD,GPIO_Pin_2);//��LEDʹ�ܶ�
	GPIO_SetBits(GPIOC,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);//�ر�LEDʹ�ܶ�
}
