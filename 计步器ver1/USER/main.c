#include "delay.h"
#include "usart.h"
#include "exti.h" 

#define maxperiodtime 1500
#define steptime 50
#define startspeed 700.f

#define ifperoidtimelimit 1  //设定是否要对单次控制的最长时长进行约束  设置1表示当控制时间到达预设的最大时间时停止控制，设置0则不约束
u8 circlecount=0;
u16 speed2run=0;
u16 temp_count_1=0;    //避免全局变量自锁问题，引发数据发送失控

 int main(void)
 {	
 
	delay_init();	    	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);	 
 	EXTIX_Init();		
	while(1)
	{	    
		 if(modeflag==1)
		{
			circlecount=(u8)(maxperiodtime/steptime);
			temp_count_1=count_1;
			while((5000+D2Cover>temp_count_1)&&circlecount&&modeflag)
			{
				speed2run=(u16)(startspeed*(5000+D2Cover-temp_count_1)/D2Cover);
				if(speed2run>99){printf("A0%d",speed2run);}
				else{printf("A0100");}
       #if ifperoidtimelimit
         circlecount--;
       #endif
				delay_ms(steptime);
				temp_count_1=count_1;
			}
			printf("A2000");
			modeflag=0;
			
			speed2run=0;
			delay_ms(steptime);
			printf("c%d",stepunit*count_1-(stepunit-1)*5000);
		}
		else if(modeflag==2)
		{
			circlecount=(u8)(maxperiodtime/steptime);
			temp_count_1=count_1;
			while((5000-D2Cover<temp_count_1)&&circlecount)
			{
				speed2run=(u16)(startspeed*(D2Cover+temp_count_1-5000)/D2Cover);
				if(speed2run>99){printf("A1%d",speed2run);}
				else{printf("A1100");}
        #if ifperoidtimelimit
         circlecount--;
        #endif
				delay_ms(steptime);
				temp_count_1=count_1;
			}
			printf("A2000");
			modeflag=0;
			speed2run=0;
			delay_ms(steptime);
			printf("c%d",stepunit*count_1-(stepunit-1)*5000);
		}
	} 
}


