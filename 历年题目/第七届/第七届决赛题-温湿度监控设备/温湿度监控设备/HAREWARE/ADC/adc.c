/*******************************************************************************  
* 文件名   : adc.c
* 描述     : ADC模数转换 
* 实验平台 ：CT117E竞赛板
* 库版本   ：ST3.5.0
* 日期     ：2017/2/18
* 作者     ：wevsmy
*******************************************************************************/
#include "adc.h"
#include "delay.h"

u16 ADC_ConvertedValue;	 //adc1传输的值

void Adc_Dma_Init(void)	  //ADC初始化使用DMA
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);
	//GPIO工作模式配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//选中管脚PB0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//设置为模拟输入
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化结构体	
	//DMA工作模式配置
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;	 //ADC地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;//内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;  //内存地址固定
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//循环传输
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	//ADC1工作模式配置	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//独立ADC模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	 //禁止扫描模式，扫描模式用于多通道采集
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//开启连续转换模式，即不停地进行ADC转换
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//不使用外部触发转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 	//采集数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	 	//要转换的通道数目1
	ADC_Init(ADC1, &ADC_InitStructure);
	//ADC时钟配置
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);  
	//ADC校准
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1)); 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

float Read_Adc(void)
{
	float temp;
	temp=(float)ADC_ConvertedValue*(3.30/0xfff);
	return temp;
}

float Read_Temp(void)
{
	float temperature;//定义为单精度型变量
	float volt;
	volt = Read_Adc();//返回最近一次ADC1规则组的转换结果
	temperature = ((80/3.3)*volt)-20;
	return temperature;//返回值为转换结果
}


