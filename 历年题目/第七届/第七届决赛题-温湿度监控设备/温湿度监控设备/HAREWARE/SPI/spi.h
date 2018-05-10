/*******************************************************************************  
* 文件名   : spi.c
* 描述     : SPI 驱动代码	 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/2/28
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __SPI_H
#define __SPI_H
#include "sys.h"

void SPI2_Init(void);				  //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet);	  //设置SPI速度
u8 SPI2_ReadWriteByte(u8 TxData);	  //SPI总线读写一个字节

#endif

