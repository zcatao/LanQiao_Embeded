/*******************************************************************************  
* �ļ���   : wkup.H
* ����     : ������������ 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2017/2/18
* ����     ��wevsmy
*******************************************************************************/
#ifndef __WKUP_H_
#define __WKUP_H_
#include "sys.h"

#define WKUP_KD PAin(0)

u8 Check_WKUP(void);
void WKUP_Init(void);
void Sys_Enter_Standby(void);

#endif
