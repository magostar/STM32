#ifndef __I2C_H

#define __I2C_H
#include "stm32f10x.h" 
void MP6050_W_SCL(uint8_t BitValue);
void MP6050_W_SDA(uint8_t BitValue);
void My_I2C_Init(void);
void My_I2C_START(void);
void My_I2C_STOP(void);
void MPU_6050_Write_Bit(uint8_t Byte);
void MPU_6050_Write_Ack(uint8_t Bit);
uint8_t MP6050_R_SCL(void);
uint8_t MP6050_R_SDA(void);
uint8_t MPU_6050_Recive_Byte(void);
uint8_t MPU_6050_Recive_Ack(void);
#endif