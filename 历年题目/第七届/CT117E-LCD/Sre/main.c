

/*********************************************\
*                   _ooOoo_                   *
*                  o8888888o                  * 
*                  88" . "88                  *
*                  (| -_- |)                  *
*                  O\  =  /O                  *
*               ____/`---'\____               * 
*             .'  \\|     |//  `.             *
*            /  \\|||  :  |||//  \            *
*           /  _||||| -:- |||||-  \           *
*           |   | \\\  -  /// |   |           *
*           | \_|  ''\---/''  |   |           *
*           \  .-\__  `-`  ___/-. /           *
*         ___`. .'  /--.--\  `. . __          *
*      ."" '<  `.___\_<|>_/___.'  >'"".       *
*     | | :  `- \`.;`\ _ /`;.`/ - ` : | |     *
*     \  \ `-.   \_ __\ /__ _/   .-` /  /     * 
*======`-.____`-.___\_____/___.-`____.-'======*
*                   `=---='                   *
*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*
*           佛祖保佑       永无BUG            *
*           楠A407					潘大叔            *
\*********************************************/


/********************************
//----------JM---------------
//内容：第七届决赛模拟题答案

//菜 B 出品

//发现bug者,可加qq：874206295交流
//作者：潘大叔分手了
//移植的童鞋，请尊重作者，著名出处

//说明：这是基于国信长天 官方板的程序
//			非官方板子需要自行修改
**********************************/




#include "stm32f10x.h"
#include "lcd.h"

#include <stdio.h>


#include "i2c.h"
#include "io.h"


//中断标志位
__IO u8 Flag_led = 0;
__IO u8 Flag_key = 0;
__IO u8 Flag_adc = 0;

//时间标志位
__IO u8 Flag_ms = 0;

//设置标志位
__IO u8 Flag_set = 0;
__IO u8 Flag_change = 0;

//状态及数据
__IO u8 Out_status = 0;
__IO u16 Frequency = 2;


//数据缓存
__IO float adc_f = 0;
__IO u16 adc_sum = 0;
__IO u16 adc_sum_temp[5];

u8 str[20];

u32 deg = 0;





u32 TimingDelay = 0;
void start_init(void);
void display_1(void);
void display_2(void);
void delay_ms(u32 nTime);



//Main Body
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	
	io_init();
	i2c_init();
	
	adc_init();
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	
	TIM3_init(0xffff,72-1);
	
	
	start_init();
	
	
	while(1)
	{
		if(Flag_key)
		{
			Flag_key = 0;
			key_read();
			
			if(key_sum==1)
			{
				Out_status ^= 0x01;
				Flag_change = 1;
				display_1();
				if(Out_status & 0x01)
					LED &=~(0x01<<0);
				else
					LED |= (0x01<<0);
				led_set();
			}
			
			if(key_sum==2)
			{
				Flag_set ^= 1;
				LCD_Clear(White);
				
				if(Flag_set)
					display_2();
				else
					display_1();
			}
			
			if((key_sum==3)&&(Flag_set))
			{
				Frequency++;if(Frequency>=10)Frequency = 10;
				Flag_change = 1;
			}
			
			if((key_sum==4)&&(Flag_set))
			{
				Frequency--;if(Frequency<=1)Frequency = 1;
				Flag_change = 1;
			}
			
		}
		
		if(Flag_adc)
		{
			static __IO u8 i=0;
			static __IO u32 deg_temp;
			
			Flag_adc = 0;
			
			adc_sum = ADC_GetConversionValue(ADC1);
			adc_sum_temp[i] = adc_sum;
			adc_f = adc_sum*3.3/4095;

			if(++i>=5)
			{
				deg=0;
				for(i=0;i<5;i++)
				deg += adc_sum_temp[i];
				deg/=5;
				deg = ( (deg*360)>>12);//0~360
				
				if(deg_temp != deg)//
				{
					deg_temp = deg;
					display_1();
					Flag_change = 1;
				}
				i=0;
			}
		}
		
		if(Flag_change)
		{
			Flag_change = 0;
			
			TIM3DEG_set(deg,Frequency,Out_status);
			
			Out_status &= (0x01);
			
			eeprom_write(0x01,Out_status);
			delay_ms(2);
			eeprom_write(0x02,Frequency);			
			delay_ms(2);
		}
		if((Flag_set)&&(Flag_ms))
		{
			Flag_ms = 0;
			
			
			display_2();
			
		}
	}
}


void start_init(void)
{
	//
	adc_sum = ADC_GetConversionValue(ADC1);
	adc_f = adc_sum*3.3/4095;
	deg = ( (adc_sum*360) >> 12);//0~360
	
	//
	Out_status = eeprom_read(0x01);
	delay_ms(2);
	Frequency  = eeprom_read(0x02);	
	delay_ms(2);
	
	if(Out_status & 0x01)
		LED &=~(0x01<<0);
	else
		LED |= (0x01<<0);
	led_set();
	
	TIM3DEG_set(deg,Frequency,Out_status);
	
	display_1();
}

void display_1(void)
{
	
	sprintf(str," ADC: %0.2fV       ",adc_f);
	LCD_DisplayStringLine(Line2,str);	
	
	if(Out_status&0x01)
	{
		sprintf(str," Output:  ON      ");
		LCD_DisplayStringLine(Line4,str);	
	}
	else
	{
		sprintf(str," Output:  OFF    ");
		LCD_DisplayStringLine(Line4,str);
	}
	
	sprintf(str,"Phase diff: %d(deg)  ",deg);
	LCD_DisplayStringLine(Line6,str);	
	
	sprintf(str,"Frequency: %dKHz  ",Frequency);
	LCD_DisplayStringLine(Line8,str);	
}

void display_2(void)
{

	sprintf(str,"     Setting  ",deg);
	LCD_DisplayStringLine(Line4,str);	
	
	sprintf(str,"  Frequency: %dKHz  ",Frequency);
	LCD_DisplayStringLine(Line7,str);	
}



//
void delay_ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}



