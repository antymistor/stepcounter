#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_rcc.h"


#define direction_def 0     //define the positve direction of rotation, 0/1

#define wheelradius 60      //define the radius of pedometer wheel, unit:mm
const float tf_factor=wheelradius*3.1415926f/360;


float pre_degree=0;
float covered_distance=0;
float covered_degree=0;

u8 CS_fl=1;
u8 CS_count=0;
u32 data_in=0;
u32 data_f=0;
u8  readfinish_f=0;
void CSN_Init(void);
void DO_Init(void);
void TIM2_Init(void);

// CSN:PB5 DO:PB14 CLK:PA0 
void SSI_init(void)
{
TIM2_Init();	
CSN_Init();
DO_Init();
pre_degree=read_degree();
covered_distance=0;
covered_degree=0;
}

void resetcounter(void)
{
pre_degree=read_degree();
covered_distance=0;
covered_degree=0;
}


void CSN_Init(void)
{   
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
}
void DO_Init(void)
{//GPIO_Mode_IPU
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void TIM2_Init(void)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE); 
	

 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  
	TIM_TimeBaseStructure.TIM_Period = 599;
	TIM_TimeBaseStructure.TIM_Prescaler =2;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE );		
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); 
    TIM_SetCompare1(TIM2,500);
	 
	TIM_Cmd(TIM2, ENABLE);  
}


float read_degree(void)
{
	float degree=0;
	CS_fl=1;
  CS_count=0;
	readfinish_f=0;
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );
	while(!readfinish_f){;}
	degree=((  (double)((data_f&0x0003ffc0)>>6)   )/4096)*360;
	TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE );
	return degree;
}

void read_distance(void)
{
	float temp_degree;
	
	temp_degree=read_degree();
	
# if direction_def
	
		if((pre_degree-temp_degree)>180)
		{covered_degree=covered_degree+360+temp_degree-pre_degree;}
		else if((temp_degree-pre_degree)>180)
		{
		covered_degree=covered_degree+temp_degree-pre_degree-360;
		}
		else
		{
		covered_degree=covered_degree+temp_degree-pre_degree;
		}
		pre_degree=temp_degree;
	
# else
	if((pre_degree-temp_degree)>180)
		{covered_degree=covered_degree-(360+temp_degree-pre_degree);}
		else if((temp_degree-pre_degree)>180)
		{
		covered_degree=covered_degree-(temp_degree-pre_degree-360);
		}
		else
		{
		covered_degree=covered_degree-(temp_degree-pre_degree);
		}
		pre_degree=temp_degree;
# endif
	covered_distance=covered_degree*tf_factor;
		

}


void TIM2_IRQHandler(void)  
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  ); 
			if(CS_fl)
			{
				if(CS_count>0)
				{
				 GPIO_ResetBits(GPIOB,GPIO_Pin_5);	
				 CS_count=0;
				 CS_fl=0;
				}
				else
				{
				  CS_count++;
				}
			}
			else
			{
				if(CS_count>16)
				{
				 data_in=(data_in<<1)+GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
				 //data_in=(data_in<<1)+1;
				 data_f=data_in;
				 readfinish_f=1;
				 data_in=0;
				 GPIO_SetBits(GPIOB,GPIO_Pin_5);	
				 CS_count=0;
				 CS_fl=1;
				}
				else
				{
				 CS_count++;
				 data_in=(data_in<<1)+GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);
				 //data_in=(data_in<<1)+1;
				}
			}
		}
}
