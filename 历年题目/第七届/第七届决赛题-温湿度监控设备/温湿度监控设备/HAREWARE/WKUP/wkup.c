/*******************************************************************************  
* �ļ���   : wkup.c
* ����     : ������������ 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2017/2/18
* ����     ��wevsmy
*******************************************************************************/
#include "wkup.h"
#include "delay.h"
#include "led.h"

void Sys_Standby(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);//ʹ��PWR����ʱ��
	PWR_WakeUpPinCmd(ENABLE);//ʹ�ܻ��ѹܽŹ���
	PWR_EnterSTANDBYMode();//�������ģʽ
}
//ϵͳ�������ģʽ
void Sys_Enter_Standby(void)
{	
	RCC_APB2PeriphResetCmd(0x01fc,DISABLE);//��λ����IO��
	Sys_Standby();
}
//���B1�ŵ��ź�
//����ֵ1����������2S����
//      0: ���󴥷�
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
//�ж���
void EXTI0_IRQHandler(void)
{
	EXTI_GetITStatus(EXTI_Line0);
	if(Check_WKUP())
	{
		Sys_Enter_Standby();	
	}
}
//����B1��ʼ��
void WKUP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//�ⲿ�жϷ�ʽ
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);//�ж���0����GPIOA.0

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
