#include "exti.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_rcc.h"

#define countmax 1000
//#define countlimit 50

u16 countlimit=(u16)(1000*stepunit/3.1415926535f/60);
u32 count_1=5000;
u16 count_2=1;

void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;

 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	  GPIO_Init(GPIOA, &GPIO_InitStructure);
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//ÏÂ½µÑØ´¥·¢
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
  	NVIC_Init(&NVIC_InitStructure);  	  
}

 
void EXTI0_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1))
	{
		count_2++;
 	  if(count_2>countlimit)
  	{
		count_2=0;
		count_1++;
	  }
	}
	else
	{
		count_2--;
		if(count_2>=countmax)
		{
			count_2=countlimit;
			count_1--;
		}
	}
//	if(!count_2)
//	{
//		printf("%d\r\n",count_1);
//	}
  EXTI_ClearITPendingBit(EXTI_Line0); 
}



