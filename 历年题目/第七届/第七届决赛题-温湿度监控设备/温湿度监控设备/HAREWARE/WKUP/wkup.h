/*******************************************************************************  
* 文件名   : wkup.H
* 描述     : 待机唤醒驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/2/18
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __WKUP_H_
#define __WKUP_H_
#include "sys.h"

#define WKUP_KD PAin(0)

u8 Check_WKUP(void);
void WKUP_Init(void);
void Sys_Enter_Standby(void);

#endif
