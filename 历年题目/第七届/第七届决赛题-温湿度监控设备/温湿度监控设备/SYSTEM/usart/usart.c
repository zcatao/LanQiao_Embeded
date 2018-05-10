#include "sys.h"
#include "usart.h"
#include "adc.h"
#include "rtc.h"
#include "timer.h"

extern int i;
int j;
extern u8 Temp_U;
extern u8 Hum_U;
extern u8 count_flag;

	  
////////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{
	/* ��SR�Ĵ����е�TC��־ */
	USART_ClearFlag(USART2,USART_FLAG_TC);
	/* ����һ���ֽ����ݵ�USART2 */
	USART_SendData(USART2, (uint8_t) ch);
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
	return (ch);
}
#endif 
#if EN_USART2_RX   //���ʹ���˽���
//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
//����2��ʼ��  
void uart_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    //USART2_TX   PA.2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    //USART2_RX	  PA.3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	//USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); //��ʼ������2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2 
}

void USART2_IRQHandler(void)                	//����2�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
	Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
	if((USART_RX_STA&0x8000)==0)//����δ���
		{
			if(USART_RX_STA&0x4000)//���յ���0x0d
			{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
			}
			else //��û�յ�0X0D
			{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
     } 
} 
void Usart_Output(void)
{
	if(USART_RX_STA&0x8000)//�жϽ������
	{
		if(USART_RX_BUF[0]=='C')
		{		
			printf("C: �¶�:%2d�� ʪ��:%2d%% ʱ��:%2d-%2d-%2d\r\n\r\n",Temp_U,Hum_U,calendar.hour,calendar.min,calendar.sec);
		}
		if(USART_RX_BUF[0]=='T')
		{	
			int x=1;
			if(count_flag==0)
			{
				for(j=0;j<i-1;j++)
				{
					printf("T: ����:%2d �¶�:%3.0f�� ʪ��:%.1f%% ʱ��:%2d-%2d-%2d\r\n",j,obj1[j].Temp_D,obj1[j].Hum_D,obj1[j].Hour_D,obj1[j].Min_D,obj1[j].Sec_D);
				}
				printf("\r\n");	
			}
			else
			{
				for(j=i+1;j<60;j++)
				{
					printf("T: ����:%2d �¶�:%3.0f�� ʪ��:%.1f%% ʱ��:%2d-%2d-%2d\r\n",x++,obj1[j].Temp_D,obj1[j].Hum_D,obj1[j].Hour_D,obj1[j].Min_D,obj1[j].Sec_D);
				}
				for(j=0;j<i-1;j++)
				{
					printf("T: ����:%2d �¶�:%3.0f�� ʪ��:%.1f%% ʱ��:%2d-%2d-%2d\r\n",x++,obj1[j].Temp_D,obj1[j].Hum_D,obj1[j].Hour_D,obj1[j].Min_D,obj1[j].Sec_D);
				}
				x=1;
				printf("\r\n");
			}					
		}
		USART_RX_STA=0;
	}		
}
#endif	

