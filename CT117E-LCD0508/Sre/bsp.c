

#include "bsp.h"
#include "stdint.h"

uint8_t	Disp_buf[3] = {1,2,3};
uint8_t	seg[17]  = { 0x3f,0x06,0x5b,0x4f, 0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c, 0x39,0x4f,0x79,0x78,0x00}; 


void GPIO_Configuration(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
}


void Seg_Display(uint8_t *buf)
{
	uint8_t	i,j;
	uint8_t	temp;

	for(j = 2; j < 3 ; j --){		
		for(i = 0 ; i < 8 ; i ++){

			if((seg[buf[j]] << i) & 0x80)
				SER_H;
			else
				SER_L;		
			SCK_H;
			SCK_L;
		}
	}
	
	RCK_H;
	RCK_L;		
	
}