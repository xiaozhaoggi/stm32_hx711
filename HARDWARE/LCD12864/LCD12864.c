#include "lcd12864.h"
#include "delay.h"




void LCD12864IO_Init(void)
{

GPIO_InitTypeDef  GPIO_InitStructure;
         
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);         
                                                                                                                        //ʹ�ܶ˿�ʱ��
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;                                                 //PA�˿�����
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                          //�������
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                         //IO���ٶ�Ϊ50MHz
GPIO_Init(GPIOA, &GPIO_InitStructure);                                                 //�����趨������ʼ��GPIOG.0
GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);                                                 //PG.0 �����

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;                
GPIO_Init(GPIOC, &GPIO_InitStructure);                                                 
GPIO_SetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);    

        
}

/**************************************************************************/
//�����ǲ���ʱ�ſ���
//��æ��־,
void RDBF(void)
{
u8 temp;
RS=0; // RS=0
RW=1; // RW=1
delay_us(1);
delay_us(1);
PA(0xFF); //������Ϊ����
while(1)
{
E=1;
delay_ms(5);
temp=PAIN;

if ((temp&0x80)==0) break;
}
E=0; // E=0
}
//д���ݵ�ָ��Ĵ���
void WRCommand(u8 comm)
{
//RDBF();
RS=0; // RS=0
RW=1; // RW=1
RW=0;
delay_ms(10);
E=1;
PA(comm);
E=0;
}
//д���ݵ����ݼĴ���
void WRData(u8 TEMP)
{
//RDBF();
RS=1; // RS=0
RW=0; // RW=1
delay_ms(10);
E=1;
PA(TEMP);
E=0;
}

/*******************************************************************/
//��ʼ��LCD-8 λ�ӿ�
void LCDInit(void)
{ 
REST=1;
delay_ms(10);
REST=0;
delay_ms(10);
REST=1;
delay_ms(10);
WRCommand(0x30); //����ָ�,8 λ����
WRCommand(0x06); //��ʼ���趨���������
WRCommand(0x01); //�����ʾDDRAM
WRCommand(0x0C); //��ʾ״̬���أ�������ʾ���������ʾ�أ������ʾ���׹�
WRCommand(0x02); //��ַ����
}

//��ʾ�����ַ���(��ʾ�������16*8 ����)
void ShowQQChar(u8 addr,u8 *english,u8 count)
{
u8 i;
WRCommand(addr);//�趨DDRAM ��ַ
for(i=0;i<count;)
{
WRData(english[i*2]);	
WRData(english[i*2+1]);
i++;
}
}

/*//��ʾ�����ַ���(��ʾ�������16*8 ����)
void ShowNUMChar(u8 addr,u8 *english,u8 count)
{
u8 i;
WRCommand(addr);//�趨DDRAM ��ַ
for(i=0;i<count;)
{
WRData(english[i*2]);
i++;
}
}*/

//��ʾ�����ִ�(����ַ�)
void ShowNUMChar(u8 addr,u8 i,u8 count)
{
u8 j;
for(j=0;j<count;)
{
WRCommand(addr);//�趨DDRAM ��ַ
WRData(i+j);
j++;
WRData(i+j);
addr++;
j++;
}
}

