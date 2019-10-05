#ifndef __CONFIG_H
#define __CONFIG_H	 
#include "sys.h"

//Pin Map:
//CSN:  PB5     DO:PB14 CLK:PA0 
//EXTI1:PA3  EXTI2:PA4
//PWM:  PA6    DIR:PA2
//USART:PA9        PA10
//Vertical Motor Ctr:
//PWM: M0:PB6 M1:PB7 M2:PB8 M3:PB9
//DIR: M0:PB0 M1:PB1 M3:PB2 M4:PB3


//�Ʋ��ֳߴ��밲װ������
#define direction_def 0     //define the positve direction of rotation, 0/1
#define wheelradius 60      //define the radius of pedometer wheel, unit:mm

//����������ز�������
#define maxperiodtime 2000   //�趨���ο����ʱ�䣬��ifperoidtimelimit=1ʱ��Ч��Unit:ms
#define steptime 20          //�趨��ѭ���Ŀ���ʱ�䣬������ʱ��,Unit:ms
#define startspeed 300.f     //�趨�����������ֵ����3phasemotor_version3֮���ֵ���˴���500������ֵĬ��100
#define ifperoidtimelimit 1  //�趨�Ƿ�Ҫ�Ե��ο��Ƶ��ʱ������Լ��  ����1��ʾ������ʱ�䵽��Ԥ������ʱ��ʱֹͣ���ƣ�����0��Լ��
#define es_co_up 8           //Estimated coefficient Ԥ��ϵ�� ,��ϵ������ֵΪϵͳ��ջ��Ĵ�ʱ��ʱ����Բ���ʱ��ı�������ֵΪ��������Ԥ��ϵ��
#define es_co_down 8         //��ֵΪ�½�����Ԥ��ϵ��
#define addedtime 400        //���������ͣתָ��󣬸���ʣ�����ЧӦ��ʱ�䣬Unit:ms

//ˮƽ�����ֵ����װ�������
#define M0 0  //��װ��0����װ1
#define M1 0
#define M2 0
#define M3 0


#endif

