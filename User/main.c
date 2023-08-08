#include "stm32f10x.h" 
#include "./OLED/oled.h"
#include "./Delay/delay.h"
#include "./SPI/spi.h"
#include "./NFR01/nf_01.h"
uint8_t T_ADDR[5]={0x01,0x02,0x03,0x04,0x05};
uint8_t data[1]={0x01};
int main(void)
{
	OLED_Init();
	My_SPI();
	Nf_01_Init();
	Nf_01_Transmit(T_ADDR);
	uint8_t temp =0x70;
  
	//Delay_s(1);
	//Nf_01_Write_Reg(NRF_WRITE_REG+CONFIG,0x53);
	//temp=Nf_01_Init_Check();
  //OLED_ShowBinNum(1,1,temp,8);
 
	while (1)
	{
	Send_Packet(data);
		Delay_ms(100);

	}
	
	
}


 