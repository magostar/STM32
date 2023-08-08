#ifndef __DMA_H

#define __DMA_H
#include "stm32f10x.h" 
void My_DMA_Init(uint32_t addrA,uint32_t addrB,uint16_t size);
void DMA_Transfer(void);
#endif