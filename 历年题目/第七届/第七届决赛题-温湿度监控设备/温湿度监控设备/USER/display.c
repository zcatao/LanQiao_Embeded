#include "display.h"
#include "delay.h"
#include "timer.h"
#include "lcd.h"
#include "led.h"
#include "adc.h"
#include "rtc.h"

char string[20];		  //字符缓冲区
float  temp;
extern u8 B1_flag;  
extern u8 B2_flag;
extern u16 LED3_flag;
extern u8 Temp_U;
extern u8 Hum_U;
extern u8 Sam_s;
extern u16 Hzval;
extern int i;

//实时数据显示界面
void Display_Data(void)
{
	/*实0时1数2据3*/
	LCD_ShowChinese(112,12,0,24,0);
	LCD_ShowChinese(112+24,12,1,24,0);
	LCD_ShowChinese(112+48,12,2,24,0);
	LCD_ShowChinese(112+72,12,3,24,0);
	/*当4前5温6度7*/
	LCD_ShowChinese(48,12+48,4,24,0);
	LCD_ShowChinese(48+24,12+48,5,24,0);
	LCD_ShowChinese(48+48,12+48,6,24,0);
	LCD_ShowChinese(48+72,12+48,7,24,0);
	/*显示当前温度℃*/
	temp = Read_Temp();	
	sprintf(string,": %3.0f",temp);	
	LCD_ShowString(48+72+24,12+48,200,24,24,(u8 *)string);
	LCD_ShowChinese(48+72+24+60,12+48,26,24,0);
	/*当4前5湿8度7*/
	LCD_ShowChinese(48,12+48*2,4,24,0);
	LCD_ShowChinese(48+24,12+48*2,5,24,0);
	LCD_ShowChinese(48+48,12+48*2,8,24,0);
	LCD_ShowChinese(48+72,12+48*2,7,24,0);
	/*显示当前湿度%*/
	sprintf(string,":  %.1f%% ",Read_Sam());	
	LCD_ShowString(48+72+24,12+48*2,200,24,24,(u8 *)string);
	/*实0时1时1钟9*/
	LCD_ShowChinese(48,12+48*3,0,24,0);
	LCD_ShowChinese(48+24,12+48*3,1,24,0);
	LCD_ShowChinese(48+48,12+48*3,1,24,0);
	LCD_ShowChinese(48+72,12+48*3,9,24,0);
	/*显示当前时间*/
	sprintf(string,": %2d-%2d-%2d",calendar.hour,calendar.min,calendar.sec);	
	LCD_ShowString(48+72+24,12+48*3,200,24,24,(u8 *)string);
	/*记10录11次12数2*/
	LCD_ShowChinese(168,12+48*4,10,24,0);
	LCD_ShowChinese(168+24,12+48*4,11,24,0);
	LCD_ShowChinese(168+48,12+48*4,12,24,0);
	LCD_ShowChinese(168+72,12+48*4,2,24,0);
	sprintf(string,": %2d",i);	
	LCD_ShowString(168+72+24,12+48*4,200,24,24,(u8 *)string);
}
//参数设置界面
void Display_Set(void)
{		
	if(B2_flag==0)	  
	{
		/*参13数2设14置15*/
		LCD_ShowChinese(112,12,13,24,0);
		LCD_ShowChinese(112+24,12,2,24,0);
		LCD_ShowChinese(112+48,12,14,24,0);
		LCD_ShowChinese(112+72,12,15,24,0);
		/*温6度7上16限17*/
		LCD_ShowChinese(48,12+48,6,24,0);
		LCD_ShowChinese(48+24,12+48,7,24,0);
		LCD_ShowChinese(48+48,12+48,16,24,0);
		LCD_ShowChinese(48+72,12+48,17,24,0);
		sprintf(string,":  %d",Temp_U);	
		LCD_ShowString(48+72+24,12+48,200,24,24,(u8 *)string);
		LCD_ShowChinese(48+72+24+60,12+48,26,24,0);	
		/*湿8度7上16限17*/
		LCD_ShowChinese(48,12+48*2,8,24,0);
		LCD_ShowChinese(48+24,12+48*2,7,24,0);
		LCD_ShowChinese(48+48,12+48*2,16,24,0);
		LCD_ShowChinese(48+72,12+48*2,17,24,0);
		sprintf(string,":  %d%s%% ",Hum_U);	
		LCD_ShowString(48+72+24,12+48*2,200,24,24,(u8 *)string);	
		/*采18样19间20隔21*/
		LCD_ShowChinese(48,12+48*3,18,24,0);
		LCD_ShowChinese(48+24,12+48*3,19,24,0);
		LCD_ShowChinese(48+48,12+48*3,20,24,0);
		LCD_ShowChinese(48+72,12+48*3,21,24,0);
		sprintf(string,":  %dS",Sam_s);	
		LCD_ShowString(48+72+24,12+48*3,200,24,24,(u8 *)string);	
		/*测22试23信24号25*/
		LCD_ShowChinese(48,12+48*4,22,24,0);
		LCD_ShowChinese(48+24,12+48*4,23,24,0);
		LCD_ShowChinese(48+48,12+48*4,24,24,0);
		LCD_ShowChinese(48+72,12+48*4,25,24,0);
		sprintf(string,": %2d.%dKHz",(Hzval/1000),((Hzval%1000)/100));
		LCD_ShowString(48+72+24,12+48*4,200,24,24,(u8 *)string);
	}
	if(B2_flag==1)		 //温度上限
	{
		/*参13数2设14置15*/
		LCD_ShowChinese(112,12,13,24,0);
		LCD_ShowChinese(112+24,12,2,24,0);
		LCD_ShowChinese(112+48,12,14,24,0);
		LCD_ShowChinese(112+72,12,15,24,0);
		/*温6度7上16限17*/
		TextColor=GREEN;
		LCD_ShowChinese(48,12+48,6,24,0);
		LCD_ShowChinese(48+24,12+48,7,24,0);
		LCD_ShowChinese(48+48,12+48,16,24,0);
		LCD_ShowChinese(48+72,12+48,17,24,0);
		sprintf(string,":  %d",Temp_U);	
		LCD_ShowString(48+72+24,12+48,200,24,24,(u8 *)string);
		LCD_ShowChinese(48+72+24+60,12+48,26,24,0);
		TextColor=BLACK;	
		/*湿8度7上16限17*/
		LCD_ShowChinese(48,12+48*2,8,24,0);
		LCD_ShowChinese(48+24,12+48*2,7,24,0);
		LCD_ShowChinese(48+48,12+48*2,16,24,0);
		LCD_ShowChinese(48+72,12+48*2,17,24,0);
		sprintf(string,":  %d%s%% ",Hum_U);	
		LCD_ShowString(48+72+24,12+48*2,200,24,24,(u8 *)string);	
		/*采18样19间20隔21*/
		LCD_ShowChinese(48,12+48*3,18,24,0);
		LCD_ShowChinese(48+24,12+48*3,19,24,0);
		LCD_ShowChinese(48+48,12+48*3,20,24,0);
		LCD_ShowChinese(48+72,12+48*3,21,24,0);
		sprintf(string,":  %dS",Sam_s);		
		LCD_ShowString(48+72+24,12+48*3,200,24,24,(u8 *)string);	
		/*测22试23信24号25*/
		LCD_ShowChinese(48,12+48*4,22,24,0);
		LCD_ShowChinese(48+24,12+48*4,23,24,0);
		LCD_ShowChinese(48+48,12+48*4,24,24,0);
		LCD_ShowChinese(48+72,12+48*4,25,24,0);
		sprintf(string,": %2d.%dKHz",(Hzval/1000),((Hzval%1000)/100));
		LCD_ShowString(48+72+24,12+48*4,200,24,24,(u8 *)string);
	}
	if(B2_flag==2)		  //湿度上限
	{
		/*参13数2设14置15*/
		LCD_ShowChinese(112,12,13,24,0);
		LCD_ShowChinese(112+24,12,2,24,0);
		LCD_ShowChinese(112+48,12,14,24,0);
		LCD_ShowChinese(112+72,12,15,24,0);
		/*温6度7上16限17*/
		LCD_ShowChinese(48,12+48,6,24,0);
		LCD_ShowChinese(48+24,12+48,7,24,0);
		LCD_ShowChinese(48+48,12+48,16,24,0);
		LCD_ShowChinese(48+72,12+48,17,24,0);
		sprintf(string,":  %d",Temp_U);	
		LCD_ShowString(48+72+24,12+48,200,24,24,(u8 *)string);
		LCD_ShowChinese(48+72+24+60,12+48,26,24,0);	
		/*湿8度7上16限17*/
		TextColor=GREEN;
		LCD_ShowChinese(48,12+48*2,8,24,0);
		LCD_ShowChinese(48+24,12+48*2,7,24,0);
		LCD_ShowChinese(48+48,12+48*2,16,24,0);
		LCD_ShowChinese(48+72,12+48*2,17,24,0);
		sprintf(string,":  %d%s%% ",Hum_U);	
		LCD_ShowString(48+72+24,12+48*2,200,24,24,(u8 *)string);
		TextColor=BLACK;	
		/*采18样19间20隔21*/
		LCD_ShowChinese(48,12+48*3,18,24,0);
		LCD_ShowChinese(48+24,12+48*3,19,24,0);
		LCD_ShowChinese(48+48,12+48*3,20,24,0);
		LCD_ShowChinese(48+72,12+48*3,21,24,0);
		sprintf(string,":  %dS",Sam_s);		
		LCD_ShowString(48+72+24,12+48*3,200,24,24,(u8 *)string);	
		/*测22试23信24号25*/
		LCD_ShowChinese(48,12+48*4,22,24,0);
		LCD_ShowChinese(48+24,12+48*4,23,24,0);
		LCD_ShowChinese(48+48,12+48*4,24,24,0);
		LCD_ShowChinese(48+72,12+48*4,25,24,0);
		sprintf(string,": %2d.%dKHz",(Hzval/1000),((Hzval%1000)/100));	
		LCD_ShowString(48+72+24,12+48*4,200,24,24,(u8 *)string);
	}
	if(B2_flag==3)		   //采样间隔
	{
		/*参13数2设14置15*/
		LCD_ShowChinese(112,12,13,24,0);
		LCD_ShowChinese(112+24,12,2,24,0);
		LCD_ShowChinese(112+48,12,14,24,0);
		LCD_ShowChinese(112+72,12,15,24,0);
		/*温6度7上16限17*/
		LCD_ShowChinese(48,12+48,6,24,0);
		LCD_ShowChinese(48+24,12+48,7,24,0);
		LCD_ShowChinese(48+48,12+48,16,24,0);
		LCD_ShowChinese(48+72,12+48,17,24,0);
		sprintf(string,":  %d",Temp_U);	
		LCD_ShowString(48+72+24,12+48,200,24,24,(u8 *)string);
		LCD_ShowChinese(48+72+24+60,12+48,26,24,0);	
		/*湿8度7上16限17*/
		LCD_ShowChinese(48,12+48*2,8,24,0);
		LCD_ShowChinese(48+24,12+48*2,7,24,0);
		LCD_ShowChinese(48+48,12+48*2,16,24,0);
		LCD_ShowChinese(48+72,12+48*2,17,24,0);
		sprintf(string,":  %d%s%% ",Hum_U);	
		LCD_ShowString(48+72+24,12+48*2,200,24,24,(u8 *)string);	
		/*采18样19间20隔21*/
		TextColor=GREEN;
		LCD_ShowChinese(48,12+48*3,18,24,0);
		LCD_ShowChinese(48+24,12+48*3,19,24,0);
		LCD_ShowChinese(48+48,12+48*3,20,24,0);
		LCD_ShowChinese(48+72,12+48*3,21,24,0);
		sprintf(string,":  %dS",Sam_s);		
		LCD_ShowString(48+72+24,12+48*3,200,24,24,(u8 *)string);
		TextColor=BLACK;	
		/*测22试23信24号25*/
		LCD_ShowChinese(48,12+48*4,22,24,0);
		LCD_ShowChinese(48+24,12+48*4,23,24,0);
		LCD_ShowChinese(48+48,12+48*4,24,24,0);
		LCD_ShowChinese(48+72,12+48*4,25,24,0);
		sprintf(string,": %2d.%dKHz",(Hzval/1000),((Hzval%1000)/100));	
		LCD_ShowString(48+72+24,12+48*4,200,24,24,(u8 *)string);
	}
	if(B2_flag==4)		   //测试信号
	{
		/*参13数2设14置15*/
		LCD_ShowChinese(112,12,13,24,0);
		LCD_ShowChinese(112+24,12,2,24,0);
		LCD_ShowChinese(112+48,12,14,24,0);
		LCD_ShowChinese(112+72,12,15,24,0);
		/*温6度7上16限17*/
		LCD_ShowChinese(48,12+48,6,24,0);
		LCD_ShowChinese(48+24,12+48,7,24,0);
		LCD_ShowChinese(48+48,12+48,16,24,0);
		LCD_ShowChinese(48+72,12+48,17,24,0);
		sprintf(string,":  %d",Temp_U);	
		LCD_ShowString(48+72+24,12+48,200,24,24,(u8 *)string);
		LCD_ShowChinese(48+72+24+60,12+48,26,24,0);	
		/*湿8度7上16限17*/
		LCD_ShowChinese(48,12+48*2,8,24,0);
		LCD_ShowChinese(48+24,12+48*2,7,24,0);
		LCD_ShowChinese(48+48,12+48*2,16,24,0);
		LCD_ShowChinese(48+72,12+48*2,17,24,0);
		sprintf(string,":  %d%s%% ",Hum_U);	
		LCD_ShowString(48+72+24,12+48*2,200,24,24,(u8 *)string);	
		/*采18样19间20隔21*/
		LCD_ShowChinese(48,12+48*3,18,24,0);
		LCD_ShowChinese(48+24,12+48*3,19,24,0);
		LCD_ShowChinese(48+48,12+48*3,20,24,0);
		LCD_ShowChinese(48+72,12+48*3,21,24,0);
		sprintf(string,":  %dS",Sam_s);		
		LCD_ShowString(48+72+24,12+48*3,200,24,24,(u8 *)string);	
		/*测22试23信24号25*/
		TextColor=GREEN;
		LCD_ShowChinese(48,12+48*4,22,24,0);
		LCD_ShowChinese(48+24,12+48*4,23,24,0);
		LCD_ShowChinese(48+48,12+48*4,24,24,0);
		LCD_ShowChinese(48+72,12+48*4,25,24,0);
		sprintf(string,": %2d.%dKHz",(Hzval/1000),((Hzval%1000)/100));		
		LCD_ShowString(48+72+24,12+48*4,200,24,24,(u8 *)string);
		TextColor=BLACK;
	}
}
//判断温度是否超上限
u8 Temp_Alarm(void)
{
	if(temp>(float)Temp_U)return 1;
	return 0;
}
//判断或湿度是否超上限
u8 Hum_Alarm(void)
{
	if(Read_Sam()>(float)Hum_U)return 1;
	return 0;
}
//报警指示功能
void Alarm_Display(void)
{
	if((Temp_Alarm()==1 && Hum_Alarm()==1)==0)
	{
		if(Temp_Alarm()==1)
		{
			LED_LE=1;
			LED1=0;
			LED_LE=0;
			delay_ms(200);
			LED_LE=1;
			LED1=1;
			LED_LE=0;
			delay_ms(200);
		}
		if(Hum_Alarm()==1)
		{
			LED_LE=1;
			LED2=0;
			LED_LE=0;
			delay_ms(200);
			LED_LE=1;
			LED2=1;
			LED_LE=0;
			delay_ms(200);
		}
	}
	if(Temp_Alarm()==1 && Hum_Alarm()==1)
	{
		LED_LE=1;
		LED1=0;LED2=0;
		LED_LE=0;
		delay_ms(200);
		LED_LE=1;
		LED1=1;LED2=1;
		LED_LE=0;
		delay_ms(200);
	}
	if(LED3_flag == 0)
	{
		LED_LE=1;
		LED3 = 1;
		LED_LE=0;
	}
	if(LED3_flag == 1)
	{
		LED_LE=1;
		LED3 = 0;
		LED_LE=0;
	}	
}


