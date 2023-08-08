#include "./IIC/i2c.h"
#include "./Delay/Delay.h"

void MP6050_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_8,(BitAction)BitValue);
	Delay_us(10);
}
void MP6050_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)BitValue);
	Delay_us(10);
}
uint8_t MP6050_R_SCL(void)
{
	uint8_t Bitvalue;
	Bitvalue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
	Delay_us(10);
	return Bitvalue;
}
uint8_t MP6050_R_SDA(void)
{
	uint8_t Bitvalue;
	Bitvalue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
	Delay_us(10);
	return Bitvalue;
}

void My_I2C_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef  GPIOB_Init_Struct;
	GPIOB_Init_Struct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIOB_Init_Struct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIOB_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Struct);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_9);
	
}
void My_I2C_START(void)
{
	MP6050_W_SDA(1);
	MP6050_W_SCL(1);
	MP6050_W_SDA(0);
	MP6050_W_SCL(0);
	
}

void My_I2C_STOP(void)
{
	MP6050_W_SDA(0);
	MP6050_W_SCL(1);
	MP6050_W_SDA(1);
}
void MPU_6050_Write_Byte(uint8_t Byte)
{
	for (uint8_t i = 0; i<8;i++)
	{
	  MP6050_W_SDA(Byte&(0x80>>i));
		MP6050_W_SCL(1);
		MP6050_W_SCL(0);
	}
}
uint8_t MPU_6050_Recive_Byte(void)
{
	uint8_t Byte=0x00;
	MP6050_W_SDA(1);
	for(uint8_t i =0 ;i<8;i++)
	{
	MP6050_W_SCL(1);
	if(MP6050_R_SDA()==1)
	{
		Byte|=0x80>>i;
	}
	MP6050_W_SCL(0);
}
	return Byte;
}

void MPU_6050_Write_Ack(uint8_t Bit)
{
	
	  MP6050_W_SDA(Bit);
		MP6050_W_SCL(1);
		MP6050_W_SCL(0);  //进入下一个时序单元
	
}
uint8_t MPU_6050_Recive_Ack(void)
{
	uint8_t Bit1=0x00;
	MP6050_W_SDA(1);
	MP6050_W_SCL(1);
  Bit1=MP6050_R_SDA();
	MP6050_W_SCL(0);
	return Bit1;
}