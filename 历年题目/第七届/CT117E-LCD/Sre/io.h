




#ifndef __IO_H
#define __IO_H



#include "stm32f10x.h"




extern __IO u16 LED;

extern __IO u8 key_sum;

extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;


void io_init(void);

void adc_init(void);




void TIM3_init(u16 arr,u16 psc);

void TIM3CH1_set(u8 status,u16 deg);
void TIM3CH2_set(u8 status,u16 deg);


void TIM3DEG_set(u16 deg,u8 fre,u8 status);

void led_set(void);

void key_read(void);





#endif
