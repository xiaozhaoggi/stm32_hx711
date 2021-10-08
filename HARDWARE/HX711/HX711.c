/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "delay.h"
#include "beep.h"

u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error=0;

//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��
#define GapValue 430


void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PB�˿�ʱ��
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);					//��ʼ������Ϊ0
}

void set_dout_gpiomode(u8 mode)// 0���� 1���
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		if(mode)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
		
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
}

//****************************************************
//��ȡHX711
//****************************************************
u32 HX711_Read(void)	//����128
{
	unsigned long count; 
	unsigned char i; 
		set_dout_gpiomode(1); //�л������ģʽ
		delay_ms(5);
  	HX711_DOUT=1; 
		delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
		set_dout_gpiomode(0);//�л�������ģʽ
		delay_ms(5);
  	while(HX711_IN); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
			delay_us(1);
			HX711_SCK=0; 
	  	if(HX711_IN)
			count++; 
		delay_us(1);
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//��25�������½�����ʱ��ת������
	delay_us(1);
	HX711_SCK=0;  
	return(count);
}






//****************************************************

//****************************************************
void Get_Maopi()
{
	Weight_Maopi = HX711_Read();
	if(Weight_Maopi > 0)
	{
	Weight_Maopi=(unsigned long)((float)Weight_Maopi/GapValue);
		if(Weight_Maopi > 20000)                //���ر���
                {        
                        Flag_Error = 1;        
                }
                else
                {  
                        Flag_Error = 0;
                }
	}
	
else
        {
                Weight_Maopi = 0;                        
        }   
	
} 



	

