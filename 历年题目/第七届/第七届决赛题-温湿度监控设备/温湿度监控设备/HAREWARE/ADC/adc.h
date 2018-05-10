/*******************************************************************************  
* 文件名   : adc.h
* 描述     : ADC模数转换 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/2/18
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __ADC_H_ 
#define	__ADC_H_
#include "sys.h"

//R37滑动变阻器 ADC初始化 
void Adc_Dma_Init(void);
float Read_Adc(void);
float Read_Temp(void);

#endif
