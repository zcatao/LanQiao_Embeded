/*******************************************************************************  
* �ļ���   : timer.C
* ����     : timer���� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/2/09
* ����     ��wevsmy
*******************************************************************************/
#include "timer.h"
#include "display.h"
#include "rtc.h"
#include "led.h"

Data_obj Data_Logging;
Data_obj obj1[60];
int i;
u8 count=0;
u8 count_flag=0;
u16 LED3_flag;

extern u8 Sam_s;
extern float  temp;

extern u8 B1_flag;
u16 a=0;


//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2��,��APB1Ϊ36M
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//Tout(ms)=(arr+1)(psc+1)/Tclk  ע��tclkΪ72M
//����ʹ�õ��Ƕ�ʱ��3
//TIM4_Int_Init(4999,7199);
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//ʱ��ʹ��
	
	TIM_TimeBaseInitStrue.TIM_Period=arr;//������һ�������¼�װ�����Զ���װ�ؼĴ������� ������5000Ϊ500ms
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 10Khz�ļ���Ƶ��
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ�ӷָ�
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);//��ʼ��ʱ�������λ

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//ʹ��TIM4�ж�

	NVIC_InitStrue.NVIC_IRQChannel=TIM4_IRQn;//TIM4�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�1
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;//�����ȼ�0
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//ʹ��
	NVIC_Init(&NVIC_InitStrue);

	TIM_Cmd(TIM4,ENABLE);//ʹ��TIMx����
}
//TIM4�жϷ�����
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//���ָ����TIM�жϷ������
	{
		count++;
		if(B1_flag==0)Display_Data();
		if(B1_flag==1)Display_Set();
		if(count>=Sam_s*2)
		{
			count=0;
			i++;
			obj1[i].Count_D=i;
			obj1[i].Temp_D=temp;
			obj1[i].Hum_D=Read_Sam();
			obj1[i].Hour_D=calendar.hour;
			obj1[i].Min_D=calendar.min;
			obj1[i].Sec_D=calendar.sec;
			if(i>=60)
			{
				i=0;count_flag=1;
			}
			LED3_flag = LED3_flag^1;
			
		}
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//����жϱ�־λ
	}	
}
/*�������ƣTTIM3_Cap_Init(u16 arr,u16 psc)
  ����      PWM�����ʼ��*/
void TIM3_Cap_Init(u16 arr,u16 psc)
{
  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM3_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
 
	//PA7 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ  
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	/*�����ж����ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM3_ICInitStructure.TIM_ICFilter = 0x0; 
 
	TIM_PWMIConfig(TIM3, &TIM3_ICInitStructure);     //PWM��������           
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);     //ѡ����Ч�����        
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);  //����Ϊ���Ӹ�λģʽ
	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);                                       
	TIM_ITConfig(TIM3, TIM_IT_CC2|TIM_IT_Update, ENABLE);          //�ж�����
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
	TIM_Cmd(TIM3, ENABLE);    
}

u16 period = 0;
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//����1���������¼�
	{		
		period = TIM_GetCapture2(TIM3);     //�ɼ�����
	}		
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update); //����жϱ�־λ
}
//TIM2 ��ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//Khz(hz)=Tclk/((arr+1)(psc+1)*2)  ע��tclkΪ72M
//��ʱ�������ͬƵ�ʷ���
void TIM2_Khz_Init(u16 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIO����

	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;//PA1
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;//�������
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	TIM_TimeBaseInitStrue.TIM_Period=arr;//������һ�������¼�װ�����Զ���װ�ؼĴ������� ������5000Ϊ500ms
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 10Khz�ļ���Ƶ��
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//����ʱ�ӷָ�
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);//��ʼ��ʱ�������λ

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//ʹ��TIM2�ж�

	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn;//TIM2�ж�ͨ��
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=7;//��ռ���ȼ�7
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;//�����ȼ�0
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//ʹ��
	NVIC_Init(&NVIC_InitStrue);
	TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2����	
}
//TIM2�жϷ�����
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		if(a == 0)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		}
		if(a == 1)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		}
		a = a^1;		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
}
//��������
//���ز��������Ƶ��KHz
float Sam_Data(void)
{
	float Sam;
	Sam=72000/(float)period;					//��������
	if(((72000/(float)period)-11)<1&&((72000/(float)period)-11)>0)Sam=1;
	if((Sam-1)<0.5&&(Sam-1)>0)Sam=1;
	if(((72000/(float)period)-7)<0.5&&((72000/(float)period)-7)>0)Sam=7;
	if(((72000/(float)period)-8)<1&&((72000/(float)period)-8)>0.5)Sam=8.5;
	if(((72000/(float)period)-9)<1&&((72000/(float)period)-9)>0.5)Sam=9.5;
	return Sam; 		
}
//ʪ�Ȳ���
//����ʪ��
float Read_Sam(void)
{
	float Samu;
	Samu=Sam_Data()*((float)80/9)+(10-(float)80/9);
	return Samu; 
}




