/*******************************************************************************  
* �ļ���   : 24c02.h
* ����     : 24c02x�������� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2017/2/21
* ����     ��wevsmy
*******************************************************************************/
#ifndef __24C02_H_ 
#define	__24C02_H_
#include "iic.h"
					  
u8 AT24C02_ReadOneByte(u16 ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24C02_WriteOneByte(u16 WriteAddr,u8 DataToWrite);		//ָ����ַд��һ���ֽ�
void AT24C02_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);//ָ����ַ��ʼд��ָ�����ȵ�����
u32 AT24C02_ReadLenByte(u16 ReadAddr,u8 Len);					//ָ����ַ��ʼ��ȡָ����������
void AT24C02_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24C02_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

u8 AT24C02_Check(void);  //�������
void AT24C02_Init(void); //��ʼ��IIC
#endif

