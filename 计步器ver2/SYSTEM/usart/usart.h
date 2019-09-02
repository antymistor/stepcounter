#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
extern u8 modeflag;  //0:stopmode 1:forwardmode 2:backwardmode
extern int D2Cover; //The distance to cover in the following peroid  Unit:mm
void uart_init(u32 bound);
#endif

