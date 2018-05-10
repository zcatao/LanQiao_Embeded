/*******************************************************************************  
* 文件名   : beep.c
* 描述     : beep驱动 蜂鸣器连接PB4，要使能端口复用功能 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/12/18
* 作者     ：wevsmy
*******************************************************************************/
#include"beep.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//初始化GPIOB与端口复用时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST,ENABLE);//函数GPIO_Remap_SWJ_NoJTRST用于除JTRST外SWJ完全使能(JTAG+SW-DP)

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;//BEEP PB4
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;//50MHz
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_4);//默认初始化为1,关闭蜂鸣器
}

