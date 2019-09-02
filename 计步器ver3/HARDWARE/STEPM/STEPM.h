#ifndef __STEPM_H
#define __STEPM_H	 
#include "sys.h"
#include "stm32f10x_tim.h"


void initEXTI(void);
void init_stepmotor(void);
void set_stepmotor(u8 sw,u8 speed);
extern u8 Dir_of_Stepmptor;

#endif

