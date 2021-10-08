/************************************************************************************
						
*************************************************************************************/
#include "HX711.h"
#include "delay.h"
#include "beep.h"

u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error=0;

//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
#define GapValue 430


void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB端口时钟
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);					//初始化设置为0
}

void set_dout_gpiomode(u8 mode)// 0输入 1输出
{
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		if(mode)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		else
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//输入上拉
		
    GPIO_Init(GPIOA, &GPIO_InitStructure);  
}

//****************************************************
//读取HX711
//****************************************************
u32 HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
		set_dout_gpiomode(1); //切换到输出模式
		delay_ms(5);
  	HX711_DOUT=1; 
		delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
		set_dout_gpiomode(0);//切换到输入模式
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
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
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
		if(Weight_Maopi > 20000)                //超重报警
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



	

