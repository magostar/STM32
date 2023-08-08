#include "./PWM/pwm.h"
 
void Moto_Init(void)
{
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	GPIO_InitTypeDef GPIOB_Init_Struct;
	GPIOB_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOB_Init_Struct.GPIO_Pin=GPIO_Pin_5;
	GPIOB_Init_Struct.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Struct);
	
	GPIOB_Init_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIOB_Init_Struct.GPIO_Pin=GPIO_Pin_6;
	GPIOB_Init_Struct.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOB_Init_Struct);
	
	GPIO_InitTypeDef GPIOA_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_2 ;
	GPIOA_Init_Struct.GPIO_Speed=GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInit_Struct;
	TIM_TimeBaseInit_Struct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit_Struct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit_Struct.TIM_Period= 20-1;
	TIM_TimeBaseInit_Struct.TIM_Prescaler =720-1;
	TIM_TimeBaseInit_Struct.TIM_RepetitionCounter =0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInit_Struct);
	TIM_InternalClockConfig(TIM2);
	
	TIM_OCInitTypeDef TIM_OCInit_Struct;
	TIM_OCStructInit(&TIM_OCInit_Struct);
	TIM_OCInit_Struct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInit_Struct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInit_Struct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInit_Struct.TIM_Pulse =10;
	TIM_OC3Init(TIM2,&TIM_OCInit_Struct);
	TIM_Cmd(TIM2,ENABLE);
	
	
}
 void Set_OC_Value(uint16_t value)
 {
	 
	 TIM_SetCompare3(TIM2,value);
	 
 }
  
