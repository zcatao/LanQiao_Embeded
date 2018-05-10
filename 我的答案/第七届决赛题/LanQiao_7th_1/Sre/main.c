#include "stm32f10x.h"
#include "hw.h"
#include "lcd.h"

u32 TimingDelay = 0;
uint8_t TimeDisplay;

int8_t CurrTemp;
uint8_t CurrHumi;
uint8_t RecordCnt;
int8_t H_UpperBound;
uint8_t T_UpperBound;
uint8_t SampleTime;
uint8_t TestSignal;  // 500Hz

Record_TypeDef Record[60];

void Delay_Ms(u32 nTime);
void Run(void);
void Main_Form(void);
void Set_Form(uint8_t);
int8_t ReadTemp(void);
void Set_Form_Sel(void);

//Main Body
int main(void)
{
	uint8_t i;
	
	SysTick_Config(SystemCoreClock/1000);

	Delay_Ms(200);
	
	HW_Init();
	
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetBackColor(White);
	LCD_SetTextColor(Black);
	
	LED_WRITE(0xa5);
	Delay_Ms(1000);
	LED_WRITE(0x5a);
	Delay_Ms(1000);
	LED_WRITE(0xff);
	
	printf(" Hello zcatao !\n");
	
	T_UpperBound = x24c02_Read(0x01);
	H_UpperBound = x24c02_Read(0x02);
	SampleTime = x24c02_Read(0x03);
	TestSignal = x24c02_Read(0x04);
	
	while(1){
		Run();		
	}
}

void Run(void)
{
	
	static enum{
		SM_MAIN_FORM = 0,
		SM_SET_FORM
	}Run_SM;
	static uint8_t i = 0;
	
	Button_Scan();	
	
	switch(Run_SM){
		case SM_MAIN_FORM :
			CurrTemp = ReadTemp();
			Main_Form();
			if(Button[0].isok){
				Button[0].isok = 0;
				LCD_Clear(White);
				Run_SM = SM_SET_FORM;
			}
			break;
		case SM_SET_FORM:
			Set_Form_Sel();			
			if(Button[0].isok){
				Button[0].isok = 0;
				LCD_Clear(White);
				x24c02_Write(0x01,T_UpperBound);
				x24c02_Write(0x02,H_UpperBound);
				x24c02_Write(0x03,SampleTime);
				x24c02_Write(0x04,TestSignal);
				Run_SM = SM_MAIN_FORM;
			}
			break;
		default :
			Run_SM = SM_MAIN_FORM;
			break;
	}	
	if(SigMsg_Query_UpperBound){
		SigMsg_Query_UpperBound = 0;
		printf("当前温度阈值:\t\t %d\n", T_UpperBound);
		printf("当前湿度阈值:\t\t %d\n", H_UpperBound);
		printf("当前时间:\t\t %0.2d:%0.2d:%0.2d\n", THH, TMM, TSS);
	}
	if(SigMsg_Query_Data){
		
		SigMsg_Query_Data = 0;
		for(i = 0; i < RecordCnt; i ++){
			printf("数据编号：%d\n",i);
			printf("\t\t 温  度 ：\t%d C \n",Record[i].T_Data);
			printf("\t\t 湿  度 ：\t%d \%\n",Record[i].H_Data);
			printf("\t\t记录时间: %0.2d:%0.2d:%0.2d\n", 
								Record[i].THH, Record[i].TMM, Record[i].TSS);
		}
	}
}
void Set_Form_Sel(void)
{	
	static enum{
		SM_SET_FORM_SEL_T = 0,
		SM_SET_FORM_SEL_H,
		SM_SET_FORM_SEL_TIME,
		SM_SET_FORM_SEL_FREQ
	}Set_Form_SM;	
	switch( Set_Form_SM){
		case SM_SET_FORM_SEL_T:
			Set_Form(1);
			if(Button[1].isok){
				Button[1].isok = 0;
				Set_Form_SM = SM_SET_FORM_SEL_H;
			}
			if(Button[2].isok){
				Button[2].isok = 0;
				T_UpperBound += 1;
				}
			if(Button[3].isok){
				Button[2].isok = 0;
				T_UpperBound -= 1;
			}
			if(T_UpperBound < -20) T_UpperBound = -20;
			if(T_UpperBound > 60)  T_UpperBound = 60;
			break;
		case SM_SET_FORM_SEL_H:
			Set_Form(2);
			if(Button[1].isok){
				Button[1].isok = 0;
				Set_Form_SM = SM_SET_FORM_SEL_TIME;
			}
			if(Button[2].isok){
				Button[2].isok = 0;
				H_UpperBound += 5;
			}
			if(Button[3].isok){
				Button[3].isok = 0;
				H_UpperBound  -= 5;
			}
			if(H_UpperBound < 10) H_UpperBound = 10;
			if(H_UpperBound > 90) H_UpperBound = 90;
			break;
		case SM_SET_FORM_SEL_TIME:
			Set_Form(3);
			if(Button[1].isok){
				Button[1].isok = 0;
				Set_Form_SM = SM_SET_FORM_SEL_FREQ;
			}
			if(Button[2].isok){
				Button[2].isok = 0;
				SampleTime += 1;
			}
			if(Button[3].isok){
				Button[3].isok = 0;
				SampleTime -= 1;
			}
			if(SampleTime < 1) SampleTime = 1;
			if(SampleTime > 5) SampleTime = 5;
			break;
		case SM_SET_FORM_SEL_FREQ:
			Set_Form(4);
			if(Button[1].isok){
				Button[1].isok = 0;
				Set_Form_SM = SM_SET_FORM_SEL_T;
			}
			if(Button[2].isok){
				Button[2].isok = 0;
				TestSignal += 1;
			}
			if(Button[3].isok){
				Button[3].isok = 0;
				TestSignal -= 1;
			}
			if(TestSignal < 2) TestSignal = 2;
			if(TestSignal >20) TestSignal = 20;
			break;				
		default : Set_Form_SM = SM_SET_FORM_SEL_T;
			break;
	}
}
void Main_Form(void)
{
	char String[41];
	//LCD_Clear(Blue);
	LCD_SetBackColor(White);
	LCD_SetTextColor(Black);
	LCD_DisplayStringLine(Line0,(unsigned char *)"                    ");	
	LCD_DisplayStringLine(Line1,(unsigned char *)"     Real Data      ");
	LCD_DisplayStringLine(Line2,(unsigned char *)"                    ");
	sprintf(String,"CurrT:   %d       ",CurrTemp);
	LCD_DisplayStringLine(Line3,(unsigned char *)String);
	sprintf(String,"CurrH:   %.2f     ",CurrHumi);
	LCD_DisplayStringLine(Line4,(unsigned char *)String);
	Time_Display(RTC_GetCounter());
	sprintf(String,"         RecCnt:%d",RecordCnt);
	LCD_DisplayStringLine(Line6,(unsigned char *)"                    ");
	LCD_DisplayStringLine(Line7,(unsigned char *)String);
	
}
	
void Set_Form(uint8_t Sel)
{
	char String[41];
	//LCD_Clear(Blue);
	LCD_SetBackColor(White);
	LCD_SetTextColor(Black);
	LCD_DisplayStringLine(Line0,(unsigned char *)"                    ");
	LCD_DisplayStringLine(Line1,(unsigned char *)"       Para Set     ");
	LCD_DisplayStringLine(Line2,(unsigned char *)"                    ");
	if(Sel == 1) {
		LCD_SetBackColor(White);
		LCD_SetTextColor(Green);
	}
	else{
		LCD_SetBackColor(White);
		LCD_SetTextColor(Black);
	}
	sprintf(String,"T_UpBound :   %d       ",T_UpperBound);
	LCD_DisplayStringLine(Line3,(unsigned char *)String);
	if(Sel == 2) {
		LCD_SetBackColor(White);
		LCD_SetTextColor(Green);
	}
	else{
		LCD_SetBackColor(White);
		LCD_SetTextColor(Black);
	}
	sprintf(String,"H_UpBound :   %d       ",H_UpperBound);
	LCD_DisplayStringLine(Line4,(unsigned char *)String);
	if(Sel == 3) {
		LCD_SetBackColor(White);
		LCD_SetTextColor(Green);
	}
	else{
		LCD_SetBackColor(White);
		LCD_SetTextColor(Black);
	}
	sprintf(String,"SampleTime:   %d     ",SampleTime);
	LCD_DisplayStringLine(Line5,(unsigned char *)String);
	if(Sel == 4) {
		LCD_SetBackColor(White);
		LCD_SetTextColor(Green);
	}
	else{
		LCD_SetBackColor(White);
		LCD_SetTextColor(Black);
	}
	sprintf(String,"TestSignal: %0.1f KHz     ",TestSignal * 0.5);
	LCD_DisplayStringLine(Line6,(unsigned char *)String);
	LCD_DisplayStringLine(Line7,(unsigned char *)"                    ");
	
}
int8_t ReadTemp(void)
{
	int8_t tmp;
	tmp = (ADCConvertedValue * 0.019532) - 20;
	if(tmp >= 60) tmp = 60;
	if(tmp <= -20) tmp = -20;
	return tmp;
}

//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}

