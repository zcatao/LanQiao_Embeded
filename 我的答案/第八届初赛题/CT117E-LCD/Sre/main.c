#include "stm32f10x.h"
#include "lcd.h"
#include "hw.h"
#include "stdio.h"

u32 TimingDelay = 0;

uint8_t Current_Platform;
uint8_t Next_Platform;
uint8_t Target_Platform_Table[4];
Run_States_enum Current_State;
uint8_t SigMsg_LCD_Flash;


void Delay_Ms(u32 nTime);
uint8_t Get_NextPlatform(void);
Run_States_enum Run(void);
void LCD_Display(void);

//Main Body
int main(void)
{
	char s[21];
	SysTick_Config(SystemCoreClock/1000);

	Delay_Ms(200);
	
	HW_Init();
	
	STM3210B_LCD_Init();
	
	LCD_Clear(White);
	LCD_SetBackColor(White);
	LCD_SetTextColor(Blue);
	
	HW_Init();
	
	while(1){

		sprintf(s,"  Next  Floor = %d  ", Next_Platform);
		LCD_DisplayStringLine(Line6,s);
		Current_State = Run();
		LCD_Display();
	}
			
}

Run_States_enum Run(void)
{
	static Run_States_enum RunMachine = SM_Initial;
	
	static uint32_t LastTime_Ms;
	static uint32_t CurrentTime_Ms;
	
	uint8_t i;
	char s[21];
	uint8_t Button_val[4] = {BUTTON_1 ,BUTTON_2, BUTTON_3, BUTTON_4};
	
	CurrentTime_Ms = GetCurrentTime_ms();
	
	sprintf(s," %d, %d ",RunMachine,(CurrentTime_Ms - LastTime_Ms)/1000);
	LCD_DisplayStringLine(Line7, (unsigned char *)s);
	
	switch (RunMachine){
		case SM_Initial:
			Current_Platform = 0;
			Next_Platform = 0;
			for(i = 0; i < 4; i ++)
				Target_Platform_Table[i] = 0;
			RunMachine = SM_IDLE;
			break;
		case SM_IDLE : 
			for( i = 0; i < 4; i ++){
				if(!Button_val[i]){
					LastTime_Ms = CurrentTime_Ms;
					Target_Platform_Table[i] = 1;
					LED_WRITE((LED_Data & ~(0x01 << i)) | (0x01 << i));
				}
			}
			if((CurrentTime_Ms - LastTime_Ms) > 1000){
				Next_Platform = Get_NextPlatform();
				LED_WRITE(LED_Data & ~(0x01 << Current_Platform));
				
				if(Next_Platform != Current_Platform){
					Set_Door_Close();
					LastTime_Ms = CurrentTime_Ms;
					RunMachine = SM_CLOSE;
				}
			}			
			break;
		case SM_CLOSE:
			if((CurrentTime_Ms - LastTime_Ms) > 4000){
				Set_ShutDown();
				if(Next_Platform > Current_Platform){
					Set_Going_Up();
					LastTime_Ms = CurrentTime_Ms;
					RunMachine = SM_GOING_UP;
				}
				else{
					Set_Going_Down();
					LastTime_Ms = CurrentTime_Ms;
					RunMachine = SM_GOING_DOWN;
				}
			}
			break;
		case SM_STAY:
			if((CurrentTime_Ms - LastTime_Ms) > 2000){
				Next_Platform = Get_NextPlatform();
				if(Next_Platform != Current_Platform){
					Set_Door_Close();
					LastTime_Ms = CurrentTime_Ms;
					RunMachine = SM_CLOSE;
				}
				else{
					LastTime_Ms = CurrentTime_Ms;
					RunMachine = SM_IDLE;
				}
			}
			break;
		case SM_OPEN:
			if((CurrentTime_Ms - LastTime_Ms) > 4000){
				Set_ShutDown();
				LastTime_Ms = CurrentTime_Ms;
				RunMachine = SM_STAY;
			}
			break;
		case SM_GOING_UP:
			if((CurrentTime_Ms - LastTime_Ms) > 6000){
				Set_ShutDown();				
				Current_Platform = Next_Platform;
				LED_WRITE(LED_Data & ~(0x01 << Current_Platform));
				Set_Door_Open();
				SigMsg_LCD_Flash = 1;
				LastTime_Ms = CurrentTime_Ms;
				RunMachine = SM_OPEN;
			}
			break;
		case SM_GOING_DOWN:
			if((CurrentTime_Ms - LastTime_Ms) > 6000){
				Set_ShutDown();
				Current_Platform = Next_Platform;
				LED_WRITE(LED_Data & ~(0x01 << Current_Platform));
				Set_Door_Open();
				SigMsg_LCD_Flash = 1;
				LastTime_Ms = CurrentTime_Ms;
				RunMachine = SM_OPEN;
			}
			break;
		default : 
				LastTime_Ms = CurrentTime_Ms;
				RunMachine = SM_IDLE;
			break;
	}
	return RunMachine;
}


uint8_t Get_NextPlatform(void)
{
	uint8_t i;
	for(i = Current_Platform; i < 4; i ++){
		if(Target_Platform_Table[i]){
			Target_Platform_Table[i] = 0;
			return i;
		}
	}
	for(i = Current_Platform; i > 0; i --){
		if(Target_Platform_Table[i]){
			Target_Platform_Table[i] = 0;
			return i;
		}
	}
	if(Target_Platform_Table[0]){
		Target_Platform_Table[0] = 0;
		return 0;
	}
	return Current_Platform;
	
}

void LCD_Display(void)
{
	static enum{
		LCD_SM_INITIAL = 0,
		LCD_SM_IDLE,
		LCD_SM_FLASH
		}LCD_Display_sm = {LCD_SM_INITIAL};
	static uint32_t CurrentTime_Ms;
	static uint32_t LastTime_Ms;
	
	char s[21];
		
	CurrentTime_Ms = GetCurrentTime_ms();
	switch(LCD_Display_sm){
		case LCD_SM_INITIAL:
			LCD_DisplayStringLine(Line1 ,(unsigned char *)" Current Platform  ");
			LCD_Display_sm = LCD_SM_IDLE;
			break;
		case LCD_SM_IDLE:
			sprintf(s,"          %d         ",Current_Platform+1);
			LCD_DisplayStringLine(Line3, (unsigned char *)s);
			if(SigMsg_LCD_Flash){
				SigMsg_LCD_Flash = 0;
				LastTime_Ms = CurrentTime_Ms;
				LCD_Display_sm = LCD_SM_FLASH;
			}
			break;
		case LCD_SM_FLASH:
			if((CurrentTime_Ms - LastTime_Ms) > 900){
				//LastTime_Ms = CurrentTime_Ms;
				sprintf(s,"          %d         ",Current_Platform+1);
				LCD_DisplayStringLine(Line3, (unsigned char *)s);
				LCD_Display_sm = LCD_SM_IDLE;
			}
			else if((CurrentTime_Ms - LastTime_Ms) > 600){
				//LastTime_Ms = CurrentTime_Ms;
				LCD_DisplayStringLine(Line3,(unsigned char *)"                    ");
			} 
			else if((CurrentTime_Ms - LastTime_Ms) > 300){
				//LastTime_Ms = CurrentTime_Ms;
				sprintf(s,"          %d         ",Current_Platform+1);
				LCD_DisplayStringLine(Line3, (unsigned char *)s);
			}
			else{
				LCD_DisplayStringLine(Line3,(unsigned char *)"                    ");
			}
			break;
		default :
			LCD_Display_sm = LCD_SM_IDLE;
	}
}

void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);	
}
