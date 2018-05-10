/*******************************************************************************  
* 文件名   : key.c
* 描述     : key驱动 PA0-B1 PA8-B2 PB1-B3 PB2-B4 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2016/12/18
* 作者     ：wevsmy
*******************************************************************************/
#include"key.h"
#include "display.h"
#include "lcd.h"
u8 Key;
u8 B1_flag=0;
u8 B2_flag=0;
u8 Temp_U;	     //温度上限变量
u8 Hum_U;		 //湿度上限变量
u8 Sam_s; 		 //采样时间变量
u16 Hzval;		 //测试信号变量  

//按键初始化函数 
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY1==0)return 1;
		else if(KEY2==0)return 2;
		else if(KEY3==0)return 3; 
		else if(KEY4==0)return 4; 
	}else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	     
	return 0;// 无按键按下
}
void Key_Scan(void)
{
	Key=KEY_Scan(0);
	switch(Key)
	{
		case KEY1_PRES:
			LCD_Clear(WHITE);
			B2_flag=0;
			B1_flag++;
			if(B1_flag>1)B1_flag=0;					
			break;
		case KEY2_PRES:
			if(B1_flag==1)
			{
				B2_flag++;
				if(B2_flag>4)B2_flag=0;
			}
			break;
		case KEY3_PRES:
			if(B2_flag==1)
			{
				Temp_U++;
				if(Temp_U>=60)Temp_U=60;
				AT24C02_WriteOneByte(0x01,Temp_U);
			}
			if(B2_flag==2)
			{
				Hum_U+=5;
				if(Hum_U>=90)Hum_U=90;
				AT24C02_WriteOneByte(0x02,Hum_U);
			}
			if(B2_flag==3)
			{
				Sam_s++;
				if(Sam_s>=5)Sam_s=5;
				AT24C02_WriteOneByte(0x03,Sam_s);
			}
			if(B2_flag==4)
			{
				Hzval+=500;
				if(Hzval>=10000)Hzval=10000;
				TIM2->ARR=(360000/Hzval)-1;
				TIM_ARRPreloadConfig(TIM2,ENABLE);
				AT24C02_WriteOneByte(0x04,(Hzval/1000)*10+(Hzval/100));
			}
			break;
		case KEY4_PRES:
			if(B2_flag==1)
			{
				Temp_U--;
				if(Temp_U<=(-20))Temp_U=(-20);
				AT24C02_WriteOneByte(0x01,Temp_U);
			}
			if(B2_flag==2)
			{
				Hum_U-=5;
				if(Hum_U<=10)Hum_U=10;
				AT24C02_WriteOneByte(0x02,Hum_U);
			}
			if(B2_flag==3)
			{
				Sam_s--;
				if(Sam_s<=1)Sam_s=1;
				AT24C02_WriteOneByte(0x03,Sam_s);
			}
			if(B2_flag==4)
			{
				Hzval-=500;
				if(Hzval<=1000)Hzval=1000;
				TIM2->ARR=(360000/Hzval)-1;	
				TIM_ARRPreloadConfig(TIM2,ENABLE);
				AT24C02_WriteOneByte(0x04,(Hzval/1000)*10+(Hzval/100));
			}
			break;
	}
}





