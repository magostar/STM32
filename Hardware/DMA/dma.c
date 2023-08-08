#include "./DMA/dma.h"

uint16_t tmp;
void My_DMA_Init(uint32_t addrA,uint32_t addrB,uint16_t size)
{
	tmp =size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	DMA_InitTypeDef DMA1_Init_Struct ;
  DMA1_Init_Struct.DMA_MemoryBaseAddr=addrB;
	DMA1_Init_Struct.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA1_Init_Struct.DMA_PeripheralBaseAddr=addrA;
	DMA1_Init_Struct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
	DMA1_Init_Struct.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
	DMA1_Init_Struct.DMA_BufferSize=size;
	DMA1_Init_Struct.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA1_Init_Struct.DMA_M2M=DMA_M2M_Enable;
	DMA1_Init_Struct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init_Struct.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init_Struct.DMA_Priority=DMA_Priority_High;
	DMA_Init(DMA1_Channel1,&DMA1_Init_Struct);
	
}
void DMA_Transfer(void)
{
	 DMA_Cmd(DMA1_Channel1,DISABLE);
	 DMA_SetCurrDataCounter(DMA1_Channel1,tmp);
	 DMA_Cmd(DMA1_Channel1,ENABLE);
	 while(DMA_GetITStatus(DMA1_IT_TC1)==RESET) ;
	DMA_ClearITPendingBit(DMA1_IT_TC1);
	
}