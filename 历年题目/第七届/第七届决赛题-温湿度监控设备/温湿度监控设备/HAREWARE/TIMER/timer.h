/*******************************************************************************  
* 文件名   : timer.H
* 描述     : timer驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/2/09
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __TIMER_H_
#define __TIMER_H_
#include "sys.h"

//数据记录结构体
typedef struct
{
	u8 Count_D;			  //
	float Temp_D;		  //温度
	float Hum_D;		  //湿度
	u8 Hour_D;			  //时
	u8 Min_D;			  //分
	u8 Sec_D; 			  //秒
} Data_obj;
extern Data_obj Data_Logging;
extern Data_obj obj1[60];

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM3_Cap_Init(u16 arr,u16 psc);
void TIM2_Khz_Init(u16 arr,u32 psc);
float Sam_Data(void);//返回捕获脉冲的频率KHz
float Read_Sam(void);

#endif
