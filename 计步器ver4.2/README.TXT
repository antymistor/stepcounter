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


//计步轮尺寸与安装方向定义
#define direction_def 0     //define the positve direction of rotation, 0/1
#define wheelradius 60      //define the radius of pedometer wheel, unit:mm

//单步控制相关参数定义
#define maxperiodtime 4000   //设定单次控制最长时间，在ifperoidtimelimit=1时生效，Unit:ms
#define steptime 20          //设定单循环的控制时间，即采样时间,Unit:ms
#define startspeed 600.f     //设定控制输出上线值，在3phasemotor_version3之后该值不宜大于600，下限值默认100
#define ifperoidtimelimit 1  //设定是否要对单次控制的最长时长进行约束  设置1表示当控制时间到达预设的最大时间时停止控制，设置0则不约束
#define es_co_up 6           //Estimated coefficient 预估系数 ,该系数理想值为系统大闭环的纯时滞时间相对采样时间的倍数，此值为上升控制预估系数
#define es_co_down 6         //该值为下降控制预估系数
#define addedtime 400        //发出卷扬机停转指令后，跟踪剩余惯性效应的时间，Unit:ms

//水平主动轮电机安装参数定义
#define M0 0                 //正装则0，反装1

#endif