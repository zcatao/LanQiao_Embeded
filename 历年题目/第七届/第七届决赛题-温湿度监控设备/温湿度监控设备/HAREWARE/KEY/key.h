/*******************************************************************************  
* �ļ���   : key.h
* ����     : key���� PA0-B1 PA8-B2 PB1-B3 PB2-B4  
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/12/18
* ����     ��wevsmy
*******************************************************************************/
#ifndef __KEY_H_
#define __KEY_H_
#include "sys.h"
#include "delay.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����1
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//��ȡ����2
#define KEY3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//��ȡ����3 
#define KEY4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//��ȡ����4 

#define KEY1_PRES 1 
#define KEY2_PRES 2
#define KEY3_PRES 3
#define KEY4_PRES 4
 
void KEY_Init(void); //������ʼ��
u8 KEY_Scan(u8 mode);
void Key_Scan(void);
#endif
