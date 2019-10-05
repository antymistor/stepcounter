#include "sys.h"
#include "delay.h"
#include "usart.h"	  
#include "stepcounter.h"
#include "STEPM.h"
#include "VERM.h"

#if 1
#pragma import(__use_no_semihosting)             
     

#define IDt 'C'
#define IDr c
u8 cnum=0;
u8 dectr[5];


// Global information that can be used in main loop
u8 modeflag=0;  //0:stopmode 1:forwardmode 2:backwardmode
int D2Cover=0; //The distance to cover in the following peroid  Unit:mm
u8 workspeed=1;

struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//??_sys_exit()??????????    
_sys_exit(int x) 
{ 
	x = x; 
} 
//???fputc?? 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//????,??????   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 


void uart_init(u32 bound){
  
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
     
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		
	NVIC_Init(&NVIC_InitStructure);	

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	

  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART1, ENABLE);                     

}

void USART1_IRQHandler(void)                	
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		Res =USART_ReceiveData(USART1);	
		if ( Res==IDt)
		{
			cnum=1;
			dectr[0]=Res;
		}
		else if(cnum>0)
		{
			if ( ( (Res>='0')&& (Res<='9') )  )
			{dectr[cnum]=Res;
			cnum++;
			}
			else
			cnum=0;
		}
		
		if(cnum==5)
		{
			cnum=0;
			if(dectr[1]=='0')         //let motor A to cover distance of 'D2Cover' in forward direction
			{ 
			  D2Cover=((dectr[2]-'0')*100+(dectr[3]-'0')*10+(dectr[4]-'0'));
				modeflag=1;
				resetcounter();
			}
			else if(dectr[1]=='1')    //let motor A to cover distance of 'D2Cover' in backward direction
			{ D2Cover=((dectr[2]-'0')*100+(dectr[3]-'0')*10+(dectr[4]-'0'));
			  modeflag=2;
				resetcounter();
			}
			else if(dectr[1]=='2')    //let it to stop motor A
			{
				modeflag=0;
				D2Cover=0;
				resetcounter();
				set_stepmotor(2,1);
				printf("A2000");
			}
			else if(dectr[1]=='3')    //let it send the value of covered distance in this moment
			{
				read_distance();
				printf("c%d",(u16)(5000+covered_distance));
			}
			else if(dectr[1]=='4')   //let work arm be controlled manually
			{
				workspeed=(dectr[3]-'0')*10+(dectr[4]-'0');
				set_stepmotor(dectr[2]-'0',workspeed);
			}
			else if(dectr[1]=='5')  //let work arm work automatically.
			{
				workspeed=(dectr[3]-'0')*10+(dectr[4]-'0');
				set_stepmotor(dectr[2]-'0',workspeed);
			}
			else if(dectr[1]=='6')  //let Robo Move in vertical direction.
			{
				workspeed=(dectr[3]-'0')*10+(dectr[4]-'0');
				RoboMove(dectr[2]-'0',workspeed);
			}
			
			
		}
	}
		
} 

