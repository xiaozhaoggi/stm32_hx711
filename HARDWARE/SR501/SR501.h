#ifndef __SR501_H
#define __SR501_H	 
#include "sys.h"


#define GPIO_FR501_RCC  RCC_AHB1Periph_GPIOB
#define GPIO_FR501_PORT GPIOB//Ñ¡ÔñGPIOA¼Ä´æÆ÷
#define GPIO_FR501_PIN  GPIO_Pin_5 //Òý½Å1

#define SR501 PBin(5)

void SR501_CONFIG(void);

		 				    
#endif

