#ifndef __UART_H

#define __UART_H
#include "stm32f10x.h" 
void Uart_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendString(char *String);
 uint8_t Serial_GetRxflag(void);
extern char Serial_RxPacket[];
extern uint8_t Serial_RxFlag;
extern char U3Serial_RxPacket[];
extern uint8_t U3Serial_RxFlag;
#endif

