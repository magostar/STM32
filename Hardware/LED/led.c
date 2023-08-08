#include "./LED/led.h"

void LED_Init()
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
 
  GPIO_InitTypeDef  GPIOA_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	
	GPIO_InitTypeDef  GPIOB_Init_Struct;
	GPIOB_Init_Struct.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIOB_Init_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIOB_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Struct);
	GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	
	EXTI_InitTypeDef EXTI0_Init_Struct;
	EXTI0_Init_Struct.EXTI_Line=EXTI_Line0;
	EXTI0_Init_Struct.EXTI_LineCmd=ENABLE;
	EXTI0_Init_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI0_Init_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI0_Init_Struct);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_Init_Struct;
	NVIC_Init_Struct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_Init_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Struct.NVIC_IRQChannelPreemptionPriority=42;
	NVIC_Init_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Init_Struct);
	
}
 void EXTI0_IRQHandler(void)
 {
	 
	 if(EXTI_GetFlagStatus(EXTI_Line0)==SET)
	 {
		 
		 EXTI_ClearITPendingBit(EXTI_Line0);
		
	 }
	 
 }
 

