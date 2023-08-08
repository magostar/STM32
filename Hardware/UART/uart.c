#include "./UART/uart.h"

char Serial_RxPacket[100];
char U3Serial_RxPacket[100];
uint8_t Serial_RxFlag;
uint8_t U3Serial_RxFlag;
void Uart_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//向电脑串口发送数据//
	GPIO_InitTypeDef GPIOA_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_9;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_10;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	
	
	GPIO_InitTypeDef GPIOB_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_10;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Struct);
	
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_11;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Struct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//USART1 对应的PA9是向电脑串口发送
	USART_InitTypeDef USART1_Init_Struct;
	USART1_Init_Struct.USART_BaudRate=9600;
	USART1_Init_Struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART1_Init_Struct.USART_Mode=USART_Mode_Tx |USART_Mode_Rx;
	USART1_Init_Struct.USART_Parity=USART_Parity_No;
	USART1_Init_Struct.USART_StopBits=USART_StopBits_1;
	USART1_Init_Struct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART1_Init_Struct);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	
	USART_InitTypeDef USART3_Init_Struct;
	USART3_Init_Struct.USART_BaudRate=9600;
	USART3_Init_Struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART3_Init_Struct.USART_Mode=USART_Mode_Tx |USART_Mode_Rx;
	USART3_Init_Struct.USART_Parity=USART_Parity_No;
	USART3_Init_Struct.USART_StopBits=USART_StopBits_1;
	USART3_Init_Struct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART3,&USART3_Init_Struct);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART3,ENABLE);
	
	
	
	NVIC_InitTypeDef NVIC_Init_Sturct;
	NVIC_Init_Sturct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Init_Sturct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Sturct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Init_Sturct.NVIC_IRQChannelSubPriority=2;

	NVIC_Init(&NVIC_Init_Sturct);
	
	NVIC_Init_Sturct.NVIC_IRQChannel=USART3_IRQn;
	NVIC_Init_Sturct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Sturct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Init_Sturct.NVIC_IRQChannelSubPriority=2;

	NVIC_Init(&NVIC_Init_Sturct);
}


void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART3, Byte);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}


void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}

void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;
	static uint8_t pRxPacket = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if (RxState == 0)
		{
			if (RxData == '@' && Serial_RxFlag == 0)
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if (RxState == 1)
		{
			if (RxData == '\r')
			{
				RxState = 2;
			}
			else
			{
				Serial_RxPacket[pRxPacket] = RxData;
				pRxPacket ++;
			}
		}
		else if (RxState == 2)
		{
			if (RxData == '\n')
			{
				RxState = 0;
				Serial_RxPacket[pRxPacket] = '\0';
				Serial_RxFlag = 1;
			}
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}



void USART3_IRQHandler(void)
{
	static uint8_t U3RxState = 0;
	static uint8_t U3pRxPacket = 0;
	if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART3);
		
		if (U3RxState == 0)
		{
			if (U3Serial_RxFlag == 0)
			{
				U3RxState = 1;
				U3pRxPacket = 0;
			}
		}
		else if (U3RxState == 1)
		{
			if (RxData == '\r')
			{
				U3RxState = 2;
			}
			else
			{
				U3Serial_RxPacket[U3pRxPacket] = RxData;
				U3pRxPacket ++;
			}
		}
		else if (U3RxState == 2)
		{
			if (RxData == '\n')
			{
				U3RxState = 0;
				U3Serial_RxPacket[U3pRxPacket] = '\0';
				U3Serial_RxFlag = 1;
			}
		}
		
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
}

