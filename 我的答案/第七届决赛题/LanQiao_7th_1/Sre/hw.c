#include "stm32f10x.h"
#include "hw.h"

uint8_t LED_Data;
uint16_t ADCConvertedValue;
Button_TypeDef Button[4];
uint8_t RxBuffer[100];
uint32_t THH = 0, TMM = 0, TSS = 0;


#define ADC1_DR_Address    ((uint32_t)0x4001244C)

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

void HW_Init(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	ADC_Configuration();
	RTC_Configuration();
	USART_Configuration();
	
	NVIC_Configuration();
}



void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// latch 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, & GPIO_InitStructure);
	// LED
	GPIO_InitStructure.GPIO_Pin = 0xff00;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, & GPIO_InitStructure);
	
	// BUTTON
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//  USART
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, & GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, & GPIO_InitStructure);
	// ADC
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOB, & GPIO_InitStructure);
	
}


void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB|
							RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD 
	, ENABLE);
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2 , ENABLE);
	  /* Enable DMA1 clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* Enable ADC1 and GPIOC clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
	
}


void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	USART_Cmd (USART2 , ENABLE);
	
}
void TIM_Configuration(void)
{
}


void ADC_Configuration(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
 /* DMA1 channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
  
  /* ADC1 configuration ------------------------------------------------------*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel14 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 reset calibration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
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
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
	  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}

void Time_Display(uint32_t TimeVar)
{
  
  char String[40];
  /* Reset RTC Counter when Time is 23:59:59 */
  if (RTC_GetCounter() == 0x0001517F)
  {
     RTC_SetCounter(0x0);
     /* Wait until last write operation on RTC registers has finished */
     RTC_WaitForLastTask();
  }
  
  /* Compute  hours */
  THH = TimeVar / 3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600) / 60;
  /* Compute seconds */
  TSS = (TimeVar % 3600) % 60;

  sprintf(String,"RTime: %0.2d:%0.2d:%0.2d", THH, TMM, TSS);
  LCD_DisplayStringLine(Line5,(unsigned char *)String);
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


void Button_Scan(void)
{
	uint8_t val = 	BUTTON_1 << 0 | 
					BUTTON_2 << 1 |
					BUTTON_3 << 2 |
					BUTTON_4 << 3;
	uint8_t tmp;
	uint8_t i ;
	
	for(i = 0 ; i < 4; i ++)
	{
		tmp = val & ( 0x01 << i );
		switch (Button[i].SM) {
			case Button_SM_IDLE :
				if(!tmp){
					Button[i].SM = Button_SM_Check;
				}
				break;
			case Button_SM_Check :
				if(!tmp){
					Button[i].SM = Button_SM_Pressed;
				}
				else{
					Button[i].SM = Button_SM_IDLE;
				}
				break;
			case Button_SM_Pressed :
				if(!tmp){
					Button[i].SM = Button_SM_Pressed;
				}
				else{
					Button[i].isok = 1;
					Button[i].SM = Button_SM_IDLE;
				}
				break;
			default : Button[i].SM = Button_SM_IDLE;
				break;
		}
	}	
}

void x24c02_Write(uint8_t addr,uint8_t data)
{
	;
}
uint8_t x24c02_Read(uint8_t addr)
{
	return 1;
}
void TestSignal_FREQ_SET(uint8_t FREQ)
{
	;
}







