/*******************************************************************************  
* �ļ���   : led.H
* ����     : LED���� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2016/12/18
* ����     ��wevsmy
*******************************************************************************/
#ifndef __LED_H_
#define __LED_H_
#include "sys.h"
/*LED�˿ڶ���*/
#define LED_LE PDout(2)//LEDʹ�ܶ˿� 1 �� 0 �ر�
//LEDΪ 1(�ߵ�ƽ)�� 0(�͵�ƽ)�� 
#define LED1 PCout(8)
#define LED2 PCout(9)
#define LED3 PCout(10)
#define LED4 PCout(11)
#define LED5 PCout(12)
#define LED6 PCout(13)
#define LED7 PCout(14)
#define LED8 PCout(15)

void LED_Init(void); //LED��ʼ��

#endif
