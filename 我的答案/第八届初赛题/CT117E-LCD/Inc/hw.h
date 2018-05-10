

#ifndef __HW_H
#define __HW_H


#include "stm32f10x.h"
#include "lcd.h"

typedef struct{
	enum{
		BUTTON_SM_IDLE = 0,
		BUTTON_SM_CHECK,
		BUTTON_SM_PRESSED,
		BUTTON_SM_RELEASE
	}sm;
	uint8_t cnt;
	uint8_t SigMsg;
}Button_TyepDef;
typedef enum{
		SM_Initial = 0,
		SM_IDLE = 1,
		SM_CLOSE,
		SM_STAY,
		SM_OPEN,
		SM_GOING_UP,
		SM_GOING_DOWN
}Run_States_enum;

extern uint8_t Current_Platform;
extern uint8_t Next_Platform;
extern uint8_t Target_Platform_Table[4];
extern Run_States_enum Current_State;



extern uint32_t TimingDelay;
extern uint8_t LED_Data;

extern Button_TyepDef Button[4];
extern uint8_t SigMsg_Button;
extern uint8_t SigMsg_LCD_Flash;



#define BUTTON_1		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)
#define BUTTON_2		GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define BUTTON_3		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define BUTTON_4		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)


#define OPEN_LATCH		GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define CLOSE_LATCH		GPIO_ResetBits(GPIOD,GPIO_Pin_2)


#define LED_WRITE(DATA)	GPIO_Write(GPIOC, GPIO_ReadOutputData(GPIOC) & 0x00ff |\
						((uint16_t)(~(LED_Data = DATA)) << 8));			\
						OPEN_LATCH;CLOSE_LATCH
						

#define LED_WRITE1(DATA) GPIOC->ODR = (GPIOC-> ODR & 0x00ff) | \
					((uint16_t)(~LED_Data = DATA) << 8);
					



void LCD_test(void);
void HW_Init(void);

void Button_Scan(void);

void GPIO_Configuration(void);
void RTC_Configuration(void);
void NVIC_Configuration(void);
void RCC_Configuration(void);
void TIM_Configuration(void);
void USART_Configuration(void);

void Set_Going_Up(void);
void Set_Going_Down(void);
void Set_Door_Close(void);
void Set_Door_Open(void);
void Set_ShutDown(void);


uint32_t GetCurrentTime_ms(void);





#endif