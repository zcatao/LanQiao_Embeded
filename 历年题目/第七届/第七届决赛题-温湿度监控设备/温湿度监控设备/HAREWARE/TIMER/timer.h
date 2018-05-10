/*******************************************************************************  
* �ļ���   : timer.H
* ����     : timer���� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/2/09
* ����     ��wevsmy
*******************************************************************************/
#ifndef __TIMER_H_
#define __TIMER_H_
#include "sys.h"

//���ݼ�¼�ṹ��
typedef struct
{
	u8 Count_D;			  //
	float Temp_D;		  //�¶�
	float Hum_D;		  //ʪ��
	u8 Hour_D;			  //ʱ
	u8 Min_D;			  //��
	u8 Sec_D; 			  //��
} Data_obj;
extern Data_obj Data_Logging;
extern Data_obj obj1[60];

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM3_Cap_Init(u16 arr,u16 psc);
void TIM2_Khz_Init(u16 arr,u32 psc);
float Sam_Data(void);//���ز��������Ƶ��KHz
float Read_Sam(void);

#endif
