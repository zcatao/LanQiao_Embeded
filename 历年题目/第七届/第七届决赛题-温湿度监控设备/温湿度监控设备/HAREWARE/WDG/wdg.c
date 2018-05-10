/*******************************************************************************  
* 文件名   : wdg.c
* 描述     : 看门狗驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/02/09
* 作者     ：wevsmy
*******************************************************************************/
#include "wdg.h"
#include "led.h"

//独立看门狗
/*
* u8 prer 预分频
* u16 rlr 重装载值
* 溢出时间(ms)计算：Tout=((4*2^prer)*rlr)/40 (M3)
*比如：IWDG_Init(4,625);//预分频为64，重装载值625，溢出时间1S
*/
void IWDG_Init(u8 prer,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //取消寄存器写保护
	IWDG_SetPrescaler(prer);//设置独立看门狗的预分频系数，确定时钟
	IWDG_SetReload(rlr);//设置看门狗的重装载值，确定溢出时间
	IWDG_ReloadCounter();//还没有使能喂狗（把重装载值先写到寄存器）
	IWDG_Enable();//使能看门狗
}
//喂独立看门狗
void IWDG_Feed(void)
{
	IWDG_ReloadCounter();	
}

//窗口看门狗
//保存WWDG计数器的设置值,默认为最大值
u8 WWDG_CNT=0x7f; 
/*初始化窗口看门狗
* tr :T[6:0],计数器值
* wr :W[6:0],窗口值
* fprer :分频系数(WDGTB),仅最低2位有效
* 溢出时间(ms)计算：Twwdg=PClk1/(4096*2^fprer)
*比如：WWDG_Init(0x7f,0x5f,WWDG_Prescaler_8);
*/
void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);//WWDG时钟使能
	WWDG_CNT=tr&WWDG_CNT;//初始化WWDG_CNT
	WWDG_SetPrescaler(fprer);//设置WWDG预分频值
	WWDG_SetWindowValue(wr);//设置窗口值
	WWDG_Enable(WWDG_CNT);//使能看门狗,设置counter
	WWDG_ClearFlag();//清除提前唤醒中断标志位
	WWDG_NVIC_Init();//初始化WWDG NVIC
	WWDG_EnableIT();//开启WWDG中断
}
//重设置WWDG计数器的值
void WWDG_Set_Counter(u8 cnt)
{
	WWDG_Enable(cnt);	
}
//WWDG中断服务初始化程序
void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn;//WWDG中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;//先占3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	NVIC_Init(&NVIC_InitStructure);//NVIC初始化		
}
//WWDG中断服务程序
void WWDG_IRQHandler(void)
{

	WWDG_SetCounter(WWDG_CNT);//当禁掉此句，WWDG将产生复位

	WWDG_ClearFlag();//清除提前唤醒中断标志位

	LED_LE=1;//打开LED使能端 
	LED8=!LED8;//闪烁LED8	
	LED_LE=0;//关闭LED使能端 			
}

