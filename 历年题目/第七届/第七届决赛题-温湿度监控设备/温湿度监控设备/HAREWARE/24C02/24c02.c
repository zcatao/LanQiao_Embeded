/*******************************************************************************  
* �ļ���   : 24c02.c
* ����     : 24c02�������� 
* ʵ��ƽ̨ ��CT117E������
* ��汾   ��ST3.5.0
* ����     ��2017/2/21
* ����     ��wevsmy
*******************************************************************************/
#include "24c02.h"

extern u8 Temp_U;	 //�¶����ޱ���
extern u8 Hum_U;		 //ʪ�����ޱ���
extern u8 Sam_s; 		 //����ʱ�����
extern u16 Hzval;		 //�����źű��� 

//��ʼ��IIC�ӿ�
void AT24C02_Init(void)
{
	IIC_Init();
	if(AT24C02_ReadOneByte(0xff)==0x88)
	{
		Temp_U=AT24C02_ReadOneByte(0x01);
		Hum_U=AT24C02_ReadOneByte(0x02);
		Sam_s=AT24C02_ReadOneByte(0x03);
		Hzval=AT24C02_ReadOneByte(0x04)*100;
	}else 
	{
		AT24C02_WriteOneByte(0xff,0x88);
		AT24C02_WriteOneByte(0x01,40);
		AT24C02_WriteOneByte(0x02,80);
		AT24C02_WriteOneByte(0x03,1);
		AT24C02_WriteOneByte(0x04,15);
		Temp_U=AT24C02_ReadOneByte(0x01);
		Hum_U=AT24C02_ReadOneByte(0x02);
		Sam_s=AT24C02_ReadOneByte(0x03);
		Hzval=AT24C02_ReadOneByte(0x04)*100;
	}
	
}
//��AT24C02ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24C02_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24C02ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24C02_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
//��AT24C02�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24C02_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24C02_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24C02�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
u32 AT24C02_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24C02_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24C02�Ƿ�����
//��������24c02�����һ����ַ(255)���洢��־��.
//����1:���ʧ��
//����0:���ɹ�
u8 AT24C02_Check(void)
{
	u8 temp;
	temp=AT24C02_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24C02_WriteOneByte(255,0X55);
	    temp=AT24C02_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24C02�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24C02_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24C02_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24C02�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24C02_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24C02_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











