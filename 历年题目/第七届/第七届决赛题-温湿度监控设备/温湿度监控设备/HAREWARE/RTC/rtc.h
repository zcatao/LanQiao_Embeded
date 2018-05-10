/*******************************************************************************  
* �ļ���   : rtc.h
* ����     : RTC���� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2017/02/16
* ����     ��wevsmy
*******************************************************************************/
#ifndef __RTC_H
#define __RTC_H	    

//ʱ��ṹ��
typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//������������
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//�����ṹ��

extern u8 const mon_table[12];	//�·��������ݱ�
u8 RTC_Init(void);        //��ʼ��RTC,����1,ʧ��;0,�ɹ�;
u8 Is_Leap_Year(u16 year);//ƽ��,�����ж�
u8 RTC_Get(void);         //����ʱ��   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//����ʱ��			 
#endif

