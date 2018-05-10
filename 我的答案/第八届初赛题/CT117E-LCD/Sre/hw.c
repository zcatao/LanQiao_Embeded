

#include "hw.h"
#include "stm32f10x.h"

uint8_t LED_Data;



Button_TyepDef Button[4];


void HW_Init(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	NVIC_Configuration();
	RTC_Configuration();
}
	
void LCD_test(void)
{
		

	LCD_DrawLine(120,0,320,Horizontal);
	LCD_DrawLine(0,160,240,Vertical);
	Delay_Ms(1000);
	LCD_Clear(Blue);

	LCD_DrawRect(70,210,100,100);
	Delay_Ms(1000);
	LCD_Clear(Blue);

	LCD_DrawCircle(120,160,50);
	Delay_Ms(1000);

	LCD_Clear(Blue);
	LCD_DisplayStringLine(Line4 ,(unsigned char *)"    Hello,world.   ");
	Delay_Ms(1000);

	LCD_SetBackColor(White);
	LCD_DisplayStringLine(Line0,(unsigned char *)"                    ");	
	LCD_SetBackColor(Black);
	LCD_DisplayStringLine(Line1,(unsigned char *)"                    ");	
	LCD_SetBackColor(Grey);
	LCD_DisplayStringLine(Line2,(unsigned char *)"                    ");
	LCD_SetBackColor(Blue);
	LCD_DisplayStringLine(Line3,(unsigned char *)"                    ");
	LCD_SetBackColor(Blue2);
	LCD_DisplayStringLine(Line4,(unsigned char *)"                    ");
	LCD_SetBackColor(Red);						
	LCD_DisplayStringLine(Line5,(unsigned char *)"                    ");
	LCD_SetBackColor(Magenta);	
	LCD_DisplayStringLine(Line6,(unsigned char *)"                    ");
	LCD_SetBackColor(Green);	
	LCD_DisplayStringLine(Line7,(unsigned char *)"                    ");	
	LCD_SetBackColor(Cyan);	
	LCD_DisplayStringLine(Line8,(unsigned char *)"                    ");
	LCD_SetBackColor(Yellow);		
	LCD_DisplayStringLine(Line9,(unsigned char *)"                    ");	
	
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// LATCH
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	// LED 
	GPIO_InitStructure.GPIO_Pin = 0xff00;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// BUTTON
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	// PWM out
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);	
}
void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
							RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE); 
	
}
void Button_Scan(void)
{
	uint8_t Button_val[4] = {BUTTON_1 ,BUTTON_2, BUTTON_3, BUTTON_4};
	uint8_t i;

	for(i = 0; i < 4; i ++)
	{
		switch ( Button[i].sm) {
			case BUTTON_SM_IDLE:
				if(!Button_val[i]){
					Button[i].cnt = 0;
					Button[i].sm = BUTTON_SM_CHECK;
				}
				break;
			case BUTTON_SM_CHECK:
				if(!Button_val[i]){
					if(Button[i].cnt < 1){
						Button[i].cnt ++;
						Button[i].sm = BUTTON_SM_CHECK;
					}
					else{
						Button[i].sm = BUTTON_SM_PRESSED;
					}
				}
				else{
					Button[i].sm = BUTTON_SM_IDLE;
				}
				break;
			case BUTTON_SM_PRESSED:
				if(!Button_val[i]){
					Button[i].sm = BUTTON_SM_PRESSED;
				}
				else{
					Button[i].sm = BUTTON_SM_RELEASE;
				}				
				break;
			case BUTTON_SM_RELEASE:
					Button[i].SigMsg = 1;
					Button[i].sm = BUTTON_SM_IDLE;
				break;
			default :
				Button[i].sm = BUTTON_SM_IDLE;
				break;
		}		
	}	
}




void RTC_Configuration(void)
{

  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSICmd(ENABLE);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(40000); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void Set_Going_Up(void)
{
	;
}
void Set_Going_Down(void)
{
	;
}
void Set_Door_Close(void){
	;
}
void Set_Door_Open(void)
{
	;
}
void Set_ShutDown(void)
{
	;
}





