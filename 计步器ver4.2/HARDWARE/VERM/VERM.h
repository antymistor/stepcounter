#ifndef __VERM_H
#define __VERM_H	 
#include "sys.h"
#include "stm32f10x_tim.h"

void init_vermotor(void);
void set_verm(u8 num,u8 dir, u16 speed);
void RoboMove(u8 dir,u8 speed);

#endif

