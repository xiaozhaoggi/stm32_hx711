#include "stm32f10x.h"
#include "delay.h"
#include "HX711.h"
#include "usart.h"
#include "beep.h"
#include "SR501.h"
#include "exti.h"
#include "lcd12864.h"
#include "usart3.h"
#include "dht11.h"

extern u8 redsence_flag;

void lcd_display(u8 *s, u8 zb, u8 data, u8 count)
{
	sprintf(s,"%d",(int)data);
	ShowQQChar(zb,s,count);
}

u8 check_redsence()
{
	if(SR501 == 0)
		{
			redsence_flag = 0;
			return 0;
		}	
		else
		{
			ShowQQChar(0x90,"�ȴ���",2);
			return 1;
		}
}

u8 check_weight()
{
	Get_Maopi();		//��ȡ����
	if(Flag_Error == 1 )
		{
			GPIO_SetBits(GPIO_BEEP_PORT,GPIO_BEEP_PIN);
			ShowQQChar(0x98,"���ݳ���",4);	
			return 1;
		}
		else
		{
			ShowQQChar(0x98,"��������",4);
			GPIO_ResetBits(GPIO_BEEP_PORT,GPIO_BEEP_PIN);	
			return 0;			
		}
}



int main(void)
{
	u8 floor = 1, dir = 1;//��ʼ¥��Ϊ1 ��������
	u8 string[20];
	u8 shang[2] = {0xa1,0xfc};//��
	u8 xia[2] = {0xa1,0xfd};//ͣ
	u8 ting[2] = {0xa3,0xad};//ͣ��gb��  ��ͬ
	u8 buffer[5];//DHT11��������������
	u16 adcx; //MQ2 AD����
	double hum;//ʪ��	
  double temp;//�¶�
	u8 weight_sta;
	char *door_sta;
	u16 times;//��ʱ��
	
	SystemInit();
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	SR501_CONFIG();	//�����ʼ��
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	LCD12864IO_Init(); 
	BEEP_CONFIG();
	Init_HX711pin();//����ģ��
	LCDInit();
	Adc_Init();
	
	ShowQQChar(0x80,"��ǰ¥��:",5);
	ShowQQChar(0x94,"MQ2:",2);
	ShowQQChar(0x8a,"��",1);
	ShowQQChar(0x8e,"%",1);
	
        
	 while(1)
	{
		delay_ms(1000);	
		delay_ms(1000);	
		adcx=Get_Adc_Average(ADC_Channel_8,10);//��ȡ����������ֵ
		sprintf(string,"%03d",adcx);
		ShowQQChar(0x96,string,2);	
		
		if (dht11_read_data(buffer) == 0)
		{
			hum = buffer[0] + buffer[1] / 10.0;
			temp = buffer[2] + buffer[3] / 10.0;
			sprintf(string,"%.1f", temp);
			ShowQQChar(0x88,string,2);
			sprintf(string,"%.1f",hum);
			ShowQQChar(0x8c,string,2);	
		} 
		
		if(Flag_Error == 1) //�������
			weight_sta = 'Y';
		else
			weight_sta = 'N';
		
		
		
		lcd_display(string, 0x85, floor, 1);
		//ShowQQChar(0x98,"���ݾ�ֹ",4);
		ShowQQChar(0x86,ting,1);
		door_sta = "OPEN";
		printf("%2.1f%2.1f%03d%c%s",temp, hum, adcx, weight_sta, door_sta);
		if(dir && floor < 6)
		{	
			
			if(check_redsence())
				continue;
			
			ShowQQChar(0x90,"������",3);
			
			delay_ms(1000);
			delay_ms(1000);

			
			if(check_redsence())
				continue;
			
			delay_ms(1000);
			delay_ms(1000);
			
			ShowQQChar(0x90,"�ѹ���",3);
			door_sta = "CLOSE";
			printf("%2.1f%2.1f%03d%c%s",temp, hum, adcx, weight_sta, door_sta);
			delay_ms(1000);
			
			if(check_weight())
				continue;
			
			ShowQQChar(0x86, shang, 1); //���ϼ�ͷ
			
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			
			floor++;
			lcd_display(string, 0x85, floor, 1);
		}
		else
			dir = 0; //����
		
		if(dir == 0 && floor > 1)
		{			
			if(check_redsence())
				continue;
			
			ShowQQChar(0x90,"������",3);
			
			delay_ms(1000);
			delay_ms(1000);
			
			if(check_redsence())
				continue;
			
			delay_ms(1000);
			delay_ms(1000);
			
			ShowQQChar(0x90,"�ѹ���",3);
			door_sta = "CLOSE";
			printf("%2.1f%2.1f%03d%c%s",temp, hum, adcx, weight_sta, door_sta);
			delay_ms(1000);
			
			if(check_weight())
				continue;
			
			ShowQQChar(0x86, xia, 1); //���¼�ͷ
			
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			
			floor--;
			lcd_display(string, 0x85, floor, 1);
		}
		else
			dir = 1; //����
		
		
		
		
	  
		
	}

}
