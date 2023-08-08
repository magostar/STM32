#include "./KEY/key.h"
bool key_flag =false;
void Key_Init()
{  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIOA_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Init_Struct;
	NVIC_Init_Struct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_Init_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Struct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Init_Struct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Init_Struct);
	
	EXTI_InitTypeDef EXTI0_Init_Struct;
	EXTI0_Init_Struct.EXTI_Line=EXTI_Line0;
	EXTI0_Init_Struct.EXTI_LineCmd=ENABLE;
	EXTI0_Init_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI0_Init_Struct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI0_Init_Struct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
}
bool EXTI_Flag(void)
{ 
	bool cnt =key_flag;
	if(key_flag==true)
	{ 
		key_flag=false;
		return cnt;
	}
	
	
}
void EXTI0_IRQHandler (void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		key_flag =true;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
	
}
