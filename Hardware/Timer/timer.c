#include "./Timer/timer.h"
extern uint16_t num;
void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
  TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIOA_Init_Struct;
	GPIOA_Init_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIOA_Init_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIOA_Init_Struct);
	
	TIM_TimeBaseInitTypeDef Tim2_Init_Struct;
	Tim2_Init_Struct.TIM_ClockDivision=TIM_CKD_DIV1;
	Tim2_Init_Struct.TIM_CounterMode=TIM_CounterMode_Up;
	Tim2_Init_Struct.TIM_Period=10-1;   //ARR的值
	Tim2_Init_Struct.TIM_Prescaler=1-1; //PSC的值
	Tim2_Init_Struct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&Tim2_Init_Struct);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitTypeDef NVIC_Init_Struct;
	NVIC_Init_Struct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Init_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init_Struct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Init_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Init_Struct);
	
	TIM_Cmd(TIM2,ENABLE);
}
void TIM2_IRQHandler(void)
{
	num++;
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
}
uint16_t Timer_GetCounter(void)
{
	
	return TIM_GetCounter(TIM2);
	
}




