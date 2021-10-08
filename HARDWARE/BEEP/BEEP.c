#include "beep.h"

//初始化PB8为输出口.并使能这个口的时钟		    
//蜂鸣器初始化

 


void BEEP_CONFIG(void)
{
	GPIO_InitTypeDef   GPIO_BEEP;
	/*配置时钟*/
	RCC_APB2PeriphClockCmd(GPIO_BEEP_RCC, ENABLE);
	GPIO_BEEP.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_BEEP.GPIO_Pin 	 = GPIO_BEEP_PIN;
	GPIO_BEEP.GPIO_Speed =GPIO_Speed_50MHz;
 
	GPIO_Init(GPIO_BEEP_PORT,&GPIO_BEEP);
	GPIO_ResetBits(GPIO_BEEP_PORT,GPIO_BEEP_PIN);//一上电蜂鸣器不响
}
