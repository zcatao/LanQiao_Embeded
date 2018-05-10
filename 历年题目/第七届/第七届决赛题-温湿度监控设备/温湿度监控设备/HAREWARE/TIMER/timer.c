/*******************************************************************************  
* 文件名   : timer.C
* 描述     : timer驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/2/09
* 作者     ：wevsmy
*******************************************************************************/
#include "timer.h"
#include "display.h"
#include "rtc.h"
#include "led.h"

Data_obj Data_Logging;
Data_obj obj1[60];
int i;
u8 count=0;
u8 count_flag=0;
u16 LED3_flag;

extern u8 Sam_s;
extern float  temp;

extern u8 B1_flag;
u16 a=0;


//通用定时器中断初始化
//这里时钟选择为APB1的2倍,而APB1为36M
//arr：自动重装值
//psc：时钟预分频数
//Tout(ms)=(arr+1)(psc+1)/Tclk  注：tclk为72M
//这里使用的是定时器3
//TIM4_Int_Init(4999,7199);
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//时钟使能
	
	TIM_TimeBaseInitStrue.TIM_Period=arr;//设置下一个更新事件装入活动的自动重装载寄存器周期 计数到5000为500ms
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//设置用来作为TIMx时钟频率除数的预分频值 10Khz的计数频率
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分割
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStrue);//初始化时间基数单位

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//使能TIM4中断

	NVIC_InitStrue.NVIC_IRQChannel=TIM4_IRQn;//TIM4中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级1
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;//从优先级0
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_Init(&NVIC_InitStrue);

	TIM_Cmd(TIM4,ENABLE);//使能TIMx外设
}
//TIM4中断服务函数
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET)//检查指定的TIM中断发生与否
	{
		count++;
		if(B1_flag==0)Display_Data();
		if(B1_flag==1)Display_Set();
		if(count>=Sam_s*2)
		{
			count=0;
			i++;
			obj1[i].Count_D=i;
			obj1[i].Temp_D=temp;
			obj1[i].Hum_D=Read_Sam();
			obj1[i].Hour_D=calendar.hour;
			obj1[i].Min_D=calendar.min;
			obj1[i].Sec_D=calendar.sec;
			if(i>=60)
			{
				i=0;count_flag=1;
			}
			LED3_flag = LED3_flag^1;
			
		}
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);//清除中断标志位
	}	
}
/*功能名称TIM3_Cap_Init(u16 arr,u16 psc)
  描述      PWM输入初始化*/
void TIM3_Cap_Init(u16 arr,u16 psc)
{
  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM3_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
 
	//PA7 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值  
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM3_ICInitStructure.TIM_Channel = TIM_Channel_2;                   
	TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;       
	TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   
	TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM3_ICInitStructure.TIM_ICFilter = 0x0; 
 
	TIM_PWMIConfig(TIM3, &TIM3_ICInitStructure);     //PWM输入配置           
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);     //选择有效输入端        
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);  //配置为主从复位模式
	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);                                       
	TIM_ITConfig(TIM3, TIM_IT_CC2|TIM_IT_Update, ENABLE);          //中断配置
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
	TIM_Cmd(TIM3, ENABLE);    
}

u16 period = 0;
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//捕获1发生捕获事件
	{		
		period = TIM_GetCapture2(TIM3);     //采集周期
	}		
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC2|TIM_IT_Update); //清除中断标志位
}
//TIM2 初始化
//arr：自动重装值
//psc：时钟预分频数
//Khz(hz)=Tclk/((arr+1)(psc+1)*2)  注：tclk为72M
//定时器输出不同频率方波
void TIM2_Khz_Init(u16 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStrue;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStrue;
	NVIC_InitTypeDef NVIC_InitStrue;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIO外设

	GPIO_InitStrue.GPIO_Pin=GPIO_Pin_1;//PA1
	GPIO_InitStrue.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStrue.GPIO_Mode=GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStrue);
	
	TIM_TimeBaseInitStrue.TIM_Period=arr;//设置下一个更新事件装入活动的自动重装载寄存器周期 计数到5000为500ms
	TIM_TimeBaseInitStrue.TIM_Prescaler=psc;//设置用来作为TIMx时钟频率除数的预分频值 10Khz的计数频率
	TIM_TimeBaseInitStrue.TIM_ClockDivision=TIM_CKD_DIV1;//设置时钟分割
	TIM_TimeBaseInitStrue.TIM_CounterMode=TIM_CounterMode_Up;//TIM向上计数模式
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStrue);//初始化时间基数单位

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能TIM2中断

	NVIC_InitStrue.NVIC_IRQChannel=TIM2_IRQn;//TIM2中断通道
	NVIC_InitStrue.NVIC_IRQChannelPreemptionPriority=7;//抢占优先级7
	NVIC_InitStrue.NVIC_IRQChannelSubPriority=0;//从优先级0
	NVIC_InitStrue.NVIC_IRQChannelCmd=ENABLE;//使能
	NVIC_Init(&NVIC_InitStrue);
	TIM_Cmd(TIM2,ENABLE);//使能TIM2外设	
}
//TIM2中断服务函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		if(a == 0)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_1);
		}
		if(a == 1)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		}
		a = a^1;		
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
}
//处理数据
//返回捕获脉冲的频率KHz
float Sam_Data(void)
{
	float Sam;
	Sam=72000/(float)period;					//计算周期
	if(((72000/(float)period)-11)<1&&((72000/(float)period)-11)>0)Sam=1;
	if((Sam-1)<0.5&&(Sam-1)>0)Sam=1;
	if(((72000/(float)period)-7)<0.5&&((72000/(float)period)-7)>0)Sam=7;
	if(((72000/(float)period)-8)<1&&((72000/(float)period)-8)>0.5)Sam=8.5;
	if(((72000/(float)period)-9)<1&&((72000/(float)period)-9)>0.5)Sam=9.5;
	return Sam; 		
}
//湿度测量
//返回湿度
float Read_Sam(void)
{
	float Samu;
	Samu=Sam_Data()*((float)80/9)+(10-(float)80/9);
	return Samu; 
}




