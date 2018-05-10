


#include "io.h"




__IO u16 LED = 0xff;


__IO u8 key_sum = 0;

__IO uint16_t CCR1_Val = 1000;
__IO uint16_t CCR2_Val = 1000;

void io_init(void)
{
	
	  GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|
                         RCC_APB2Periph_AFIO, ENABLE);
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST, ENABLE);

		//led
    GPIO_InitStructure.GPIO_Pin = 0xff00;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
		
		//key
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIOC->ODR |= (0xffff);
		GPIOD->ODR |= (0x01<<2);
		GPIOD->ODR &=~(0x01<<2);


}





void adc_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
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



void TIM3_init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_DeInit(TIM3);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	/* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_Prescaler = psc/2;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);



  TIM_Cmd(TIM3, ENABLE);

	
  /* Enable the TIM3 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
}



void TIM3DEG_set(u16 deg,u8 fre,u8 status)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_DeInit(TIM3);
	
	TIM3_init(0xffff,72-1);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
	if(status)
	{
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	}
	else
	{
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	}
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
	
	//-------CCR1-----------
	CCR1_Val = (1000)/fre;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;//
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	//-------CCR2-----------
	CCR2_Val = (1000)/fre;
	TIM_OCInitStructure.TIM_Pulse = (CCR2_Val + CCR2_Val*deg/180);//CCR2_Val;//
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	

  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);
	
	if(status)
	{
		TIM_ITConfig(TIM3, TIM_IT_CC1|TIM_IT_CC2 , ENABLE);
		TIM_Cmd(TIM3, ENABLE);
	}
	else
	{
		TIM_ITConfig(TIM3, TIM_IT_CC1|TIM_IT_CC2 , DISABLE);
		TIM_Cmd(TIM3, DISABLE);
	}
}




void led_set(void)
{
	GPIOC->ODR = (LED<<8);
	
	GPIOD->ODR |= (0x01<<2);

	GPIOD->ODR &=~(0x01<<2);
}




void key_read(void)
{
	key_sum = 0;
	
	if((GPIOA->IDR&0x01)==0)
	{
		while((GPIOA->IDR&0x01)==0);
		
		key_sum = 1;
		
	}
	
	if((GPIOA->IDR&0x100)==0)
	{
		while((GPIOA->IDR&0x100)==0);
		
		key_sum = 2;
		
	}
	if((GPIOB->IDR&0x02)==0)
	{
		while((GPIOB->IDR&0x02)==0);
		
		key_sum = 3;
		
	}
	if((GPIOB->IDR&0x04)==0)
	{
		while((GPIOB->IDR&0x04)==0);
		
		key_sum = 4;
		
	}
	
	
	
}





