/*******************************************************************************  
* �ļ���   : wdg.h
* ����     : ���Ź����� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/02/09
* ����     ��wevsmy
*******************************************************************************/
#ifndef __WDG_H_
#define __WDG_H_
#include "sys.h"
//�������Ź�
void IWDG_Init(u8 prer,u16 rlr); //�������Ź���ʼ��
void IWDG_Feed(void);//ι��
//���ڿ��Ź� 
void WWDG_Init(u8 tr,u8 wr,u32 fprer); //���ڿ��Ź���ʼ��
void WWDG_Set_Counter(u8 cnt);//������WWDG��������ֵ
void WWDG_NVIC_Init(void);//WWDG�жϷ����ʼ������

#endif
