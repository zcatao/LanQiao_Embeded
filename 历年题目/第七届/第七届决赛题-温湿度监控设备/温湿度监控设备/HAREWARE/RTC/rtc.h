/*******************************************************************************  
* 文件名   : rtc.h
* 描述     : RTC驱动 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/02/16
* 作者     ：wevsmy
*******************************************************************************/
#ifndef __RTC_H
#define __RTC_H	    

//时间结构体
typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//公历日月年周
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//日历结构体

extern u8 const mon_table[12];	//月份日期数据表
u8 RTC_Init(void);        //初始化RTC,返回1,失败;0,成功;
u8 Is_Leap_Year(u16 year);//平年,闰年判断
u8 RTC_Get(void);         //更新时间   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//设置时间			 
#endif

