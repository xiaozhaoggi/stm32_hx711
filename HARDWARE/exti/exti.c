#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "SR501.h"
#include "lcd12864.h"



u8 redsence_flag;
 
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		SR501_CONFIG();
    //GPIOB.3 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器




  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 


 
}

//外部中断0服务程序 
void EXTI3_IRQHandler(void)
{
	
	delay_ms(10);

  redsence_flag = 1;
				
	
	
  EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE0上的中断标志位
}
 
