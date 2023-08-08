#include "./ADC/adc.h"
uint32_t ad_value[];
void ADC1_Init (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
//	GPIO_InitTypeDef  GPIOA_Init_Struct ;
//	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_AIN;
//	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_4;
//	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_16,1,ADC_SampleTime_239Cycles5);
	ADC_InitTypeDef ADC1_Init_Struct;
	ADC1_Init_Struct.ADC_ContinuousConvMode=ENABLE;
	ADC1_Init_Struct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC1_Init_Struct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC1_Init_Struct.ADC_Mode=ADC_Mode_Independent;
	ADC1_Init_Struct.ADC_NbrOfChannel=1;
	ADC1_Init_Struct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC1_Init_Struct);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_InitTypeDef DMA1_Init_Struct ;
  DMA1_Init_Struct.DMA_MemoryBaseAddr=(uint32_t)ad_value;
	DMA1_Init_Struct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA1_Init_Struct.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;
	DMA1_Init_Struct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA1_Init_Struct.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA1_Init_Struct.DMA_BufferSize=1;
	DMA1_Init_Struct.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA1_Init_Struct.DMA_M2M=DMA_M2M_Disable;
	DMA1_Init_Struct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init_Struct.DMA_Mode=DMA_Mode_Circular;
	DMA1_Init_Struct.DMA_Priority=DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DMA1_Init_Struct);
	ADC_Cmd(ADC1,ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
  ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1)==SET);
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1)==SET);
}

