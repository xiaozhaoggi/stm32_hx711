#include "beep.h"

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��

 


void BEEP_CONFIG(void)
{
	GPIO_InitTypeDef   GPIO_BEEP;
	/*����ʱ��*/
	RCC_APB2PeriphClockCmd(GPIO_BEEP_RCC, ENABLE);
	GPIO_BEEP.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_BEEP.GPIO_Pin 	 = GPIO_BEEP_PIN;
	GPIO_BEEP.GPIO_Speed =GPIO_Speed_50MHz;
 
	GPIO_Init(GPIO_BEEP_PORT,&GPIO_BEEP);
	GPIO_ResetBits(GPIO_BEEP_PORT,GPIO_BEEP_PIN);//һ�ϵ����������
}
