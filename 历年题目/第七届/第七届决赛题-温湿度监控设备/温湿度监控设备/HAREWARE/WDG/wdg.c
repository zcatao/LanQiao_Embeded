/*******************************************************************************  
* �ļ���   : wdg.c
* ����     : ���Ź����� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/02/09
* ����     ��wevsmy
*******************************************************************************/
#include "wdg.h"
#include "led.h"

//�������Ź�
/*
* u8 prer Ԥ��Ƶ
* u16 rlr ��װ��ֵ
* ���ʱ��(ms)���㣺Tout=((4*2^prer)*rlr)/40 (M3)
*���磺IWDG_Init(4,625);//Ԥ��ƵΪ64����װ��ֵ625�����ʱ��1S
*/
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ȡ���Ĵ���д����
	IWDG_SetPrescaler(prer);//���ö������Ź���Ԥ��Ƶϵ����ȷ��ʱ��
	IWDG_SetReload(rlr);//���ÿ��Ź�����װ��ֵ��ȷ�����ʱ��
	IWDG_ReloadCounter();//��û��ʹ��ι��������װ��ֵ��д���Ĵ�����
	IWDG_Enable();//ʹ�ܿ��Ź�
}
//ι�������Ź�
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();	
}

//���ڿ��Ź�
//����WWDG������������ֵ,Ĭ��Ϊ���ֵ
u8 WWDG_CNT=0x7f; 
/*��ʼ�����ڿ��Ź�
* tr :T[6:0],������ֵ
* wr :W[6:0],����ֵ
* fprer :��Ƶϵ��(WDGTB),�����2λ��Ч
* ���ʱ��(ms)���㣺Twwdg=PClk1/(4096*2^fprer)
*���磺WWDG_Init(0x7f,0x5f,WWDG_Prescaler_8);
*/
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);//WWDGʱ��ʹ��
	WWDG_CNT=tr&WWDG_CNT;//��ʼ��WWDG_CNT
	WWDG_SetPrescaler(fprer);//����WWDGԤ��Ƶֵ
	WWDG_SetWindowValue(wr);//���ô���ֵ
	WWDG_Enable(WWDG_CNT);//ʹ�ܿ��Ź�,����counter
	WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
	WWDG_NVIC_Init();//��ʼ��WWDG NVIC
	WWDG_EnableIT();//����WWDG�ж�
}
//������WWDG��������ֵ
void WWDG_Set_Counter(u8 cnt)
{
	WWDG_Enable(cnt);	
}
//WWDG�жϷ����ʼ������
void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn;//WWDG�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//��ռ3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	NVIC_Init(&NVIC_InitStructure);//NVIC��ʼ��		
}
//WWDG�жϷ������
void WWDG_IRQHandler(void)
{

	WWDG_SetCounter(WWDG_CNT);//�������˾䣬WWDG��������λ

	WWDG_ClearFlag();//�����ǰ�����жϱ�־λ

	LED_LE=1;//��LEDʹ�ܶ� 
	LED8=!LED8;//��˸LED8	
	LED_LE=0;//�ر�LEDʹ�ܶ� 			
}

