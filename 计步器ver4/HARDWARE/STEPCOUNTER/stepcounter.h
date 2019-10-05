#ifndef __STEPCOUNTER_H
#define __STEPCOUNTER_H	 
#include "sys.h"
#include "stm32f10x_tim.h"


void SSI_init(void);
float read_degree(void);
void read_distance(void);
void resetcounter(void);
extern float covered_distance;
#endif

