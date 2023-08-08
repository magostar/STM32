#include "./SPI/spi.h"

void My_SPI_W_CSN(uint8_t BitValue)  //设置模块的片选引脚  
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_6,(BitAction)BitValue); 
}
void My_SPI_W_CE(uint8_t BitValue)  //设置模块的模式选择引脚  
{
	GPIO_WriteBit(GPIOC,GPIO_Pin_5,(BitAction)BitValue); 
}
void My_SPI_W_SCK(uint8_t BitValue)  //设置模块的片选引脚
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)BitValue); 
}
void My_SPI_W_MOSI(uint8_t BitValue)  //设置模块的片选引脚
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)BitValue); 
}
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}
uint8_t MySPI_R_IRQ(void)
{
	return GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4);
}
void My_SPI(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef  GPIO_Init_Struct;
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_5;  //pin6-csn||||pin5-ce
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Init_Struct);
	
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_4;  //pin4-IRQ
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_Init_Struct);
	
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_7;   //pin7-mosi||pin5-sck
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Struct);
	
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_6;             //pin6-miso
	GPIO_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Init_Struct);

}
void MySPI_Start(void)
{
	My_SPI_W_CSN(0);
}
void MySPI_Stop(void)
{
	My_SPI_W_CSN(1);
}
uint8_t MySPI_RW_Byte(uint8_t addr)
{
	uint8_t ByteReceive=0x00;
  for(uint8_t i=0; i<8;i++)
	{
	My_SPI_W_MOSI(addr&(0x80>>i));
	My_SPI_W_SCK(1);
	if(	MySPI_R_MISO()==1)
	{
		ByteReceive |=(0x80>>i);
	}
	My_SPI_W_SCK(0);
}
	return ByteReceive;
}