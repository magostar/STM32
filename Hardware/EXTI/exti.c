#include "./EXTI/exti.h"
int16_t cnt = 0;
extern  uint16_t num;



void Exti_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef  GPIOA_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	//GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Init_Struct_1;
	NVIC_Init_Struct_1.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_Init_Struct_1.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Struct_1.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_Init_Struct_1.NVIC_IRQChannelSubPriority=2;
  NVIC_Init(&NVIC_Init_Struct_1);
	
	NVIC_InitTypeDef NVIC_Init_Struct_2;
	NVIC_Init_Struct_2.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_Init_Struct_2.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Struct_2.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Init_Struct_2.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Init_Struct_2);
	
	
	EXTI_InitTypeDef  EXTI_Init_Struct;
	EXTI_Init_Struct.EXTI_Line=EXTI_Line2|EXTI_Line3;
	EXTI_Init_Struct.EXTI_LineCmd=ENABLE;
	EXTI_Init_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Init_Struct.EXTI_Trigger= EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Init_Struct);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource2);
 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);

} 
  

int  Encoder_Get(void)
{
  int16_t Temp;
	Temp =cnt;
	cnt=0;
	return Temp;
	
}



void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)==1)
	{
	 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==0)
	 {
		  cnt++;
		 
	 }
		 EXTI_ClearITPendingBit(EXTI_Line2);
 }
	
	
		
	
}
void  EXTI3_IRQHandler(void)
{
	
	if(EXTI_GetITStatus(EXTI_Line3)==1)
	{
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==0)
	 {	
		 cnt--;
		
		
	 }
	 EXTI_ClearITPendingBit(EXTI_Line3);
	}
	
	
}
	
	
	
	
	

