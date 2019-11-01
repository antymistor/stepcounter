#include "VERM.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "config.h"

//Vertical Motor Ctr:
//PWM: M0:PB6 M1:PB7 M2:PB8 M3:PB9
//DIR: M0:PB0 M1:PB1 M3:PB2 M4:PB3
void init_vermotor(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
	TIM_OCInitTypeDef              TIM_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
	
	TIM_DeInit(TIM4);
	
	TIM_TimeBaseStructure.TIM_Period=999;                
  TIM_TimeBaseStructure.TIM_Prescaler=71;     
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM4, ENABLE);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                              
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;    
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;    
  TIM_OCInitStructure.TIM_Pulse=0;
  
  TIM_OC1Init(TIM4,&TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
  
	TIM_Cmd(TIM4,ENABLE);
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
	
	TIM_SetCompare1(TIM4,0);
	
}


void RoboMove(u8 dir,u8 speed)
{
#if M0
			if(!dir){GPIO_ResetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed*10);}
			else if(dir==1){GPIO_SetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed*10);}
#else
			if(dir==1){GPIO_ResetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed*10);}
			else if(!dir){GPIO_SetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed*10);}
#endif
      else{TIM_SetCompare1(TIM4,0);}
}





