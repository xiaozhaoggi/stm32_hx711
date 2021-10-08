#ifndef __BEEP_H
#define __BEEP_H	 
#include "sys.h"
#include "stm32f10x.h"



#define GPIO_BEEP_RCC  RCC_APB2Periph_GPIOA
#define GPIO_BEEP_PORT GPIOA//Ñ¡ÔñGPIOA¼Ä´æÆ÷
#define GPIO_BEEP_PIN  GPIO_Pin_12 //Òý½Å12


void BEEP_CONFIG(void);

		 				    
#endif


