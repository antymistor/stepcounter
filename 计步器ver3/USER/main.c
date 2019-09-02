#include "delay.h"
#include "usart.h"
#include "exti.h" 
#include "STEPM.h"
#define maxperiodtime 2000
#define steptime 20
#define startspeed 300.f

#define ifperoidtimelimit 1  //�趨�Ƿ�Ҫ�Ե��ο��Ƶ��ʱ������Լ��  ����1��ʾ������ʱ�䵽��Ԥ������ʱ��ʱֹͣ���ƣ�����0��Լ��

#define es_co_up 8 //Estimated coefficient Ԥ��ϵ�� ,��ϵ������ֵΪϵͳ��ջ��Ĵ�ʱ��ʱ��Կ������ڵı���
#define es_co_down 8
#define addedtime 400//���������ͣתָ��󣬸���ʣ�����ЧӦ��ʱ��
u8 circlecount=0;
u16 speed2run=0;
int speed_count=0;    //����ȫ�ֱ����������⣬�������ݷ���ʧ��
float pre_distance=0;

u8 i=0;
 int main(void)
 {	
 
	delay_init();	    	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);	 
 	SSI_init();
	 
	initEXTI();
  init_stepmotor();
	 
	while(1)
	{	    
		 if(modeflag==1)
		{ 
			resetcounter();
			pre_distance=0;
			circlecount=(u8)(maxperiodtime/steptime);
			read_distance();
			speed_count=(int)(covered_distance-pre_distance);
			pre_distance=covered_distance;
			while((D2Cover>pre_distance+speed_count*es_co_up)&&circlecount&&modeflag==1)
			{
				speed2run=(u16)(startspeed*(D2Cover-pre_distance)/D2Cover);
				if(speed2run>99){printf("A0%d",speed2run);}
				else{printf("A0100");}
        printf("c%d\r\n",(u16)(5000+covered_distance));
       #if ifperoidtimelimit
         circlecount--;
       #endif
				delay_ms(steptime);
				read_distance();
				speed_count=(int)(covered_distance-pre_distance);
			  pre_distance=covered_distance;
			}
			
			modeflag=0;
			speed2run=0;
			i=addedtime/steptime;
			
			while(i--)
			{
			printf("A2000");
			read_distance();
	    printf("c%d",(u16)(5000+covered_distance));
			delay_ms(steptime);
			}
			//resetcounter();
			//printf("A2000");
		}
		else if(modeflag==2)
		{
			resetcounter();
			pre_distance=0;
			circlecount=(u8)(maxperiodtime/steptime);
			read_distance();
			speed_count=(int)(pre_distance-covered_distance);
			pre_distance=covered_distance;
			while((speed_count*es_co_down<pre_distance+D2Cover)&&circlecount&&modeflag==2)
			{ 
				speed2run=(u16)(startspeed*(D2Cover+pre_distance)/D2Cover);
				if(speed2run>99){printf("A1%d",speed2run);}
				else{printf("A1050");}
				printf("c%d\r\n",(u16)(5000+covered_distance));
        #if ifperoidtimelimit
         circlecount--;
        #endif
				delay_ms(steptime);
				read_distance();
				speed_count=(int)(pre_distance-covered_distance);
		    pre_distance=covered_distance;
			}
			
			
			modeflag=0;
			speed2run=0;
			i=addedtime/steptime;
			
			while(i--)
			{
			printf("A2000");
			 printf("c%d",(u16)(5000+covered_distance));
			delay_ms(steptime);
			}
//		resetcounter();
		}
		delay_ms(500);
		read_distance();
		 printf("c%d",(u16)(5000+covered_distance));
	} 
}


