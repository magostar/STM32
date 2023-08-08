#ifndef __SPI_H
#include "stm32f10x.h" 
void My_SPI_W_CSN(uint8_t BitValue);
void My_SPI_W_CE(uint8_t BitValue);
void My_SPI_W_SCK(uint8_t BitValue);
void My_SPI_W_MOSI(uint8_t BitValue);
uint8_t MySPI_R_MISO(void);
void My_SPI(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_R_IRQ(void);
uint8_t MySPI_RW_Byte(uint8_t Byte);
#define __SPI_H

#endif