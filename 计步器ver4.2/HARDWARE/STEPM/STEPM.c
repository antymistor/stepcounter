
#include "STEPM.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"

u8 Dir_of_Stepmptor=0;

//CSN:PB5 DO:PB14 CLK:PA0 

//EXTI1:PA3  EXTI2:PA4

//PWM:PA6 DIR:PA2

//USART: PA9 PA10
void initEXTI(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;

 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	  GPIO_Init(GPIOA, &GPIO_InitStructure);
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource3);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//?????
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 

	  EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	 
	
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure);  	  
		
		
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;	
		NVIC_Init(&NVIC_InitStructure);  	
}
void EXTI3_IRQHandler(void)
{
	delay_ms(1);
	if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))
	{
  	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	}
  EXTI_ClearITPendingBit(EXTI_Line3); 
}


void EXTI4_IRQHandler(void)
{
	delay_ms(1);
	if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4))
	{
  	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}

  EXTI_ClearITPendingBit(EXTI_Line4); 
}


void init_stepmotor(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_OCInitTypeDef              TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	
	TIM_DeInit(TIM3);
	
	
	TIM_TimeBaseStructure.TIM_Period=200;                
  TIM_TimeBaseStructure.TIM_Prescaler=999;     
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM3, ENABLE);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                              
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;    
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    
  TIM_OCInitStructure.TIM_Pulse=100;
  
  TIM_OC1Init(TIM3,&TIM_OCInitStructure);  
	
	
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
	TIM_Cmd(TIM3,DISABLE);
	TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_SetCompare1(TIM3,100);
}


void set_stepmotor(u8 sw,u8 speed)
{
  //TIM_Cmd(TIM2,DISABLE);
	if(speed){
	if(!sw)
	{
		TIM3->PSC=(u16)(999/speed);
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		TIM_Cmd(TIM3,ENABLE);
	}
	else if(sw==1)
	{
		TIM3->PSC=(u16)(999/speed);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		TIM_Cmd(TIM3,ENABLE);
	}
	else
	{
		//TIM3->PSC=(u16)(99/speed);
		//
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		TIM_Cmd(TIM3,DISABLE);
	}
  }
}
