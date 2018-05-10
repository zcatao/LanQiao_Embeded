

#ifndef	__BSP_H
#define __BSP_H


#include "stm32f10x.h"
#include "stdint.h"

#define SER_H		( GPIO_SetBits( GPIOA ,GPIO_Pin_1))
#define SER_L		( GPIO_ResetBits( GPIOA, GPIO_Pin_1))

#define RCK_H		(GPIO_SetBits(GPIOA, GPIO_Pin_2))
#define RCK_L		(GPIO_ResetBits(GPIOA, GPIO_Pin_2))

#define SCK_H		(GPIO_SetBits(GPIOA, GPIO_Pin_3))
#define SCK_L		(GPIO_ResetBits(GPIOA, GPIO_Pin_3))





#define SEG_HOLD	


void GPIO_Configuration(void);
void Seg_Display(uint8_t *buf);

extern uint8_t Disp_buf[3];




#endif 

