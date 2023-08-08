#include "./NFR01/nf_01.h"
#include "./SPI/spi.h"
#include "./Delay/delay.h"

void Nf_01_Init(void)
{
	My_SPI_W_SCK(0);
	My_SPI_W_CE(0);
	My_SPI_W_CSN(1);
}
uint8_t Nf_01_Write_Reg_Byte(uint8_t addr,uint8_t byte)
{   uint8_t status;
	  MySPI_Start();
	  Delay_us(1);
	  status=MySPI_RW_Byte(addr);
	  Delay_us(1);
	  MySPI_RW_Byte(byte);
	  Delay_us(1);
	  MySPI_Stop();
	  return status;
}

uint8_t Nf_01_Write_Reg(uint8_t addr,uint8_t *data,uint8_t length)
{   uint8_t status;
	  MySPI_Start();
	  Delay_us(1);
	status=MySPI_RW_Byte(addr);
	 for(uint8_t i = 0 ; i<length;i++)
	{
	  MySPI_RW_Byte(data[i]);
	}
	  MySPI_Stop();
	  Delay_us(1);
	  return status;
}

uint8_t Nf_01_Read_Reg_Byte(uint8_t reg)
{
  uint8_t value =0x00;
  MySPI_Start();
	Delay_us(1);
  MySPI_RW_Byte(reg);
	Delay_us(1);
	value=MySPI_RW_Byte(NOP);
	Delay_us(1);
	My_SPI_W_CSN(1);
  return(value);
}

uint8_t Nf_01_Read_Reg(uint8_t reg,uint8_t *data,uint8_t length)
{
  uint8_t status =0x00;
  MySPI_Start();
	Delay_us(1);
  status=MySPI_RW_Byte(reg);
  for(uint8_t i =0 ; i<length;i++)
	{
	*(data+i)=MySPI_RW_Byte(NOP);        //i=0ʱ data��Ӧ����data[0],iҲΪ0
	
	}
	My_SPI_W_CSN(1);
	Delay_us(1);
  return(status);
}

uint8_t Nf_01_Init_Check(void)
{
	uint8_t output[5]={0xFF,0xFF,0xFF,0xFF,0xFF};
	uint8_t input[5];
	Nf_01_Write_Reg(NRF_WRITE_REG+TX_ADDR,output,TX_ADR_WIDTH);
	Nf_01_Read_Reg(NRF_READ_REG+TX_ADDR,input,TX_ADR_WIDTH);   //����ȥ�������ַ���Ѿ��������ֵ���ı���
	for(uint8_t i=0;i<TX_ADR_WIDTH;i++)
	{
		if(output[i]!=input[i])  //�����ʱ�򷵻�1����ѭ���������ظ��ж�
		{
			return 1;
		}
		
	}
	return 0;
}
void Nf_01_Listen(uint8_t *addr)
{
		 My_SPI_W_CE(0);
	 Nf_01_Write_Reg(NRF_WRITE_REG + TX_ADDR, addr, RX_ADR_WIDTH);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + EN_AA, 0x01);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + EN_RXADDR, 0x01);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + RF_CH, 40);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + RF_SETUP, 0x0f);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + CONFIG, 0x0f);
   My_SPI_W_CE(1);
}
	void Nf_01_Transmit(uint8_t *addr)
{
	 My_SPI_W_CE(0);
	 Nf_01_Write_Reg(NRF_WRITE_REG + TX_ADDR, addr, TX_ADR_WIDTH);
	 Nf_01_Write_Reg(NRF_WRITE_REG + RX_ADDR_P0, addr, TX_ADR_WIDTH);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + EN_AA, 0x01);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + EN_RXADDR, 0x01);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + SETUP_RETR, 0x1a);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + RF_CH, 40);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + RF_SETUP, 0x0f);
	 Nf_01_Write_Reg_Byte(NRF_WRITE_REG + CONFIG, 0x0e);
   My_SPI_W_CE(1);
}
	void Nf_01_Received_Data(uint8_t * data)
	{
		uint8_t status;
		Nf_01_Read_Reg(RD_RX_PLOAD,data,RX_PLOAD_WIDTH);
		status = Nf_01_Read_Reg_Byte(RD_RX_PLOAD);
		Nf_01_Write_Reg_Byte(NRF_WRITE_REG+STATUS,status);
	}
	
uint8_t Send_Packet(uint8_t * buf)
 { 
	 uint8_t state;
My_SPI_W_CE	(0);											//CE���ͣ�ʹ��24L01����
Nf_01_Write_Reg(WR_TX_PLOAD,buf,TX_PLOAD_WIDTH);	//д���ݵ�TX FIFO,32���ֽ�
My_SPI_W_CE(1) ;   									    //CE�øߣ�ʹ�ܷ���	   
	
	while(MySPI_R_IRQ() == 1);										//�ȴ��������
	state=Nf_01_Read_Reg_Byte(STATUS);  						//��ȡ״̬�Ĵ�����ֵ	   
	Nf_01_Write_Reg_Byte(NRF_WRITE_REG+STATUS,state); 			//���TX_DS��MAX_RT�жϱ�־
	if(state&0x10)			   						    //�ﵽ����ط�����
	{
		Nf_01_Write_Reg_Byte(FLUSH_TX,0xff);					//���TX FIFO�Ĵ��� 
		return 0x10; 
	}
	if(state&0x20)									        //�������
	{
		return 0x20;
	}
	return 0XFF;	 		

 } 