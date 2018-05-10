
#include "stm32f10x.h"


//	uart
#define M_PA3		RXD2
#define M_PA2		TXD2
#define M_PA10		RXD1
#define M_PA9		TXD1

//	I2C
#define M_PB6		SCL
#define N_PB7		SDA

//	buz and latch
#define M_PD2		N_LE
#define M_PB4		N_BUZ

//	Button
#define M_PA0		N_K1
#define M_PA8		N_K2
#define	M_PB1		N_K3
#define M_PB2		N_K4

//	data
#define M_PC0		L_D0
#define M_PC1		L_D1
#define M_PC2		L_D2
#define M_PC3		L_D3
#define M_PC4		L_D4
#define M_PC5		L_D5
#define M_PC6		L_D6
#define M_PC7		L_D7	
#define M_PC8		H_D0
#define M_PC9		H_D1
#define M_PC10		H_D2
#define M_PC11		H_D3
#define M_PC12		H_D4
#define M_PC13		H_D5
#define M_PC14		H_D6
#define M_PC15		H_D7


#define LED1	H_D0
#define LED2	H_D1
#define LED3	H_D2


uint16_t i;
int main()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = 
	
	return 0;
}