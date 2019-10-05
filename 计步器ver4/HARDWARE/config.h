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


//¼Æ²½ÂÖ³ß´çÓë°²×°·½Ïò¶¨Òå
#define direction_def 0     //define the positve direction of rotation, 0/1
#define wheelradius 60      //define the radius of pedometer wheel, unit:mm

//µ¥²½¿ØÖÆÏà¹Ø²ÎÊı¶¨Òå
#define maxperiodtime 2000   //Éè¶¨µ¥´Î¿ØÖÆ×î³¤Ê±¼ä£¬ÔÚifperoidtimelimit=1Ê±ÉúĞ§£¬Unit:ms
#define steptime 20          //Éè¶¨µ¥Ñ­»·µÄ¿ØÖÆÊ±¼ä£¬¼´²ÉÑùÊ±¼ä,Unit:ms
#define startspeed 300.f     //Éè¶¨¿ØÖÆÊä³öÉÏÏßÖµ£¬ÔÚ3phasemotor_version3Ö®ºó¸ÃÖµ²»ÒË´óÓÚ500£¬ÏÂÏŞÖµÄ¬ÈÏ100
#define ifperoidtimelimit 1  //Éè¶¨ÊÇ·ñÒª¶Ôµ¥´Î¿ØÖÆµÄ×î³¤Ê±³¤½øĞĞÔ¼Êø  ÉèÖÃ1±íÊ¾µ±¿ØÖÆÊ±¼äµ½´ïÔ¤ÉèµÄ×î´óÊ±¼äÊ±Í£Ö¹¿ØÖÆ£¬ÉèÖÃ0Ôò²»Ô¼Êø
#define es_co_up 8           //Estimated coefficient Ô¤¹ÀÏµÊı ,¸ÃÏµÊıÀíÏëÖµÎªÏµÍ³´ó±Õ»·µÄ´¿Ê±ÖÍÊ±¼äÏà¶Ô²ÉÑùÊ±¼äµÄ±¶Êı£¬´ËÖµÎªÉÏÉı¿ØÖÆÔ¤¹ÀÏµÊı
#define es_co_down 8         //¸ÃÖµÎªÏÂ½µ¿ØÖÆÔ¤¹ÀÏµÊı
#define addedtime 400        //·¢³ö¾íÑï»úÍ£×ªÖ¸Áîºó£¬¸ú×ÙÊ£Óà¹ßĞÔĞ§Ó¦µÄÊ±¼ä£¬Unit:ms

//Ë®Æ½Ö÷¶¯ÂÖµç»ú°²×°²ÎÊı¶¨Ò
#define M0 0  //Õı×°Ôò0£¬·´×°1
#define M1 0
#define M2 0
#define M3 0


#endif

