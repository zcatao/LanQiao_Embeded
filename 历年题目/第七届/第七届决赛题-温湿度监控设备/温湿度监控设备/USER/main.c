/* Includes ------------------------------------------------------------------*/
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "led.h"
#include "display.h"
#include "adc.h"
#include "rtc.h"
#include "key.h"
#include "timer.h"
#include "24c02.h"

extern uint16_t period;
extern u16 Hzval; 

int main(void)
{	 		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);	
	delay_init();	
	uart_init(9600);
	AT24C02_Init();	
	LCD_Init();
	LED_Init();
	Adc_Dma_Init();
	KEY_Init();	
	while(RTC_Init());	
	TIM4_Int_Init(4999,7199);
	TIM3_Cap_Init(0xffff,0);			
	TIM2_Khz_Init(((360000/Hzval)-1),99);
	while(1)
	{		
		Key_Scan();	
		Usart_Output();
		Alarm_Display();		
	}	 
}


/******************************************END OF FILE*************************/
