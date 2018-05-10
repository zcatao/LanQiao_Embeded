

#ifndef HW_H_
#define HW_H_

#include "stm32f10x.h"
#include "lcd.h"
#include "i2c.h"
#include <stdio.h>

typedef struct{
	enum{
		Button_SM_IDLE = 0,
		Button_SM_Check,
		Button_SM_Pressed,
		Button_SM_Release
	}SM;
	uint8_t isok;
} Button_TypeDef;

typedef struct {
	uint8_t THH;
	uint8_t TMM;
	uint8_t TSS;
	uint8_t T_Data;
	uint8_t H_Data;
}Record_TypeDef;

extern uint8_t LED_Data;
extern Button_TypeDef Button[4];
extern uint16_t ADCConvertedValue;
extern uint8_t RxBuffer[100];
extern uint8_t TimeDisplay;
extern uint8_t SigMsg_Query_UpperBound;
extern uint8_t SigMsg_Query_Data;
extern uint32_t THH, TMM, TSS;
extern Record_TypeDef Record[60];
extern uint8_t RecordCnt;
extern uint8_t SigMsg_Record;
extern uint8_t SigMsg_1s;

void HW_Init(void);
void LCD_test(void);
void Button_Scan(void);
void Delay_Ms(uint32_t nTime);
void GPIO_Configuration(void);
void RCC_Configuration(void);
void TIM_Configuration(void);
void ADC_Configuration(void);
void RTC_Configuration(void);
void USART_Configuration(void);
void NVIC_Configuration(void);
void EXTI_Configuration(void);
void Time_Display(uint32_t TimeVar);
void x24c02_Write(uint8_t addr, uint8_t data);
uint8_t x24c02_Read(uint8_t addr);
void TestSignal_FREQ_SET(uint8_t FREQ);

#define OPEN_LATCH			GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define CLOSE_LATCH			GPIO_ResetBits(GPIOD, GPIO_Pin_2)

#define LED_WRITE(DATA)		GPIO_Write(GPIOC, GPIO_ReadInputData(GPIOC) & 0x00ff |\
							((uint16_t)(LED_Data = (uint8_t)DATA) << 8)) ;\
							OPEN_LATCH;CLOSE_LATCH
#define BUTTON_1			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define BUTTON_2			GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define BUTTON_3			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define BUTTON_4			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)




#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */







#endif