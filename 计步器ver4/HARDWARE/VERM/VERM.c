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
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	
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
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);  
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);  
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM4,&TIM_OCInitStructure);  
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  
	TIM_Cmd(TIM4,ENABLE);
	TIM_CtrlPWMOutputs(TIM4,ENABLE);
	
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare2(TIM4,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
}


void set_verm(u8 num,u8 dir, u16 speed)
{
  switch (num)
	{
		case 0:
#if M0
			if(!dir){GPIO_ResetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed);}
			else if(dir==1){GPIO_SetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed);}
#else
			if(dir==1){GPIO_ResetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed);}
			else if(!dir){GPIO_SetBits(GPIOB,GPIO_Pin_0);TIM_SetCompare1(TIM4,speed);}
#endif
      else{TIM_SetCompare1(TIM4,0);}
      break;	
			
		case 1:
#if M1
			if(!dir){GPIO_ResetBits(GPIOB,GPIO_Pin_1);TIM_SetCompare2(TIM4,speed);}
			else if(dir==1){GPIO_SetBits(GPIOB,GPIO_Pin_1);TIM_SetCompare2(TIM4,speed);}
#else
			if(dir==1){GPIO_ResetBits(GPIOB,GPIO_Pin_1);TIM_SetCompare2(TIM4,speed);}
			else if(!dir){GPIO_SetBits(GPIOB,GPIO_Pin_1);TIM_SetCompare2(TIM4,speed);}
#endif
      else{TIM_SetCompare2(TIM4,0);}
      break;

		case 2:
#if M2
			if(!dir){GPIO_ResetBits(GPIOB,GPIO_Pin_2);TIM_SetCompare3(TIM4,speed);}
			else if(dir==1){GPIO_SetBits(GPIOB,GPIO_Pin_2);TIM_SetCompare3(TIM4,speed);}
#else
			if(dir==1){GPIO_ResetBits(GPIOB,GPIO_Pin_2);TIM_SetCompare3(TIM4,speed);}
			else if(!dir){GPIO_SetBits(GPIOB,GPIO_Pin_2);TIM_SetCompare3(TIM4,speed);}
#endif
      else{TIM_SetCompare3(TIM4,0);}
      break;
			
		case 3:
#if M3
			if(!dir){GPIO_ResetBits(GPIOB,GPIO_Pin_3);TIM_SetCompare4(TIM4,speed);}
			else if(dir==1){GPIO_SetBits(GPIOB,GPIO_Pin_3);TIM_SetCompare4(TIM4,speed);}
#else
			if(dir==1){GPIO_ResetBits(GPIOB,GPIO_Pin_3);TIM_SetCompare4(TIM4,speed);}
			else if(!dir){GPIO_SetBits(GPIOB,GPIO_Pin_3);TIM_SetCompare4(TIM4,speed);}
#endif
			
      else{TIM_SetCompare4(TIM4,0);}
      break;
		default:break;
	}
}

void RoboMove(u8 dir,u8 speed)
{
		set_verm(0,dir,(u16)speed*10);
	  set_verm(1,dir,(u16)speed*10);
		set_verm(2,dir,(u16)speed*10);
		set_verm(3,dir,(u16)speed*10);
}





