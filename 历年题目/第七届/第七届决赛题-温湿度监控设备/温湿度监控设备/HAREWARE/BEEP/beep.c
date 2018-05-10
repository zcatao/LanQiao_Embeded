/*******************************************************************************  
* �ļ���   : beep.c
* ����     : beep���� ����������PB4��Ҫʹ�ܶ˿ڸ��ù��� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/12/18
* ����     ��wevsmy
*******************************************************************************/
#include"beep.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//��ʼ��GPIOB��˿ڸ���ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);//����GPIO_Remap_SWJ_NoJTRST���ڳ�JTRST��SWJ��ȫʹ��(JTAG+SW-DP)

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//BEEP PB4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//�����������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHz
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_4);//Ĭ�ϳ�ʼ��Ϊ1,�رշ�����
}

