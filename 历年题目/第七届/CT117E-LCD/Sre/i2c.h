#ifndef  __I2C_H__
#define  __I2C_H__


#include "stm32f10x.h"


void i2c_init(void);
void delay1(unsigned int n);

void I2CStart(void);
void I2CStop(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
unsigned char I2CWaitAck(void);

void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);


void eeprom_write(u8 add,u8 dat);

u8 eeprom_read(u8 add);



#endif
