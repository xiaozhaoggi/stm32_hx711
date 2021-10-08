#include "lcd12864.h"
#include "delay.h"




void LCD12864IO_Init(void)
{

GPIO_InitTypeDef  GPIO_InitStructure;
         
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);         
                                                                                                                        //使能端口时钟
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;                                                 //PA端口配置
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                          //推挽输出
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                         //IO口速度为50MHz
GPIO_Init(GPIOA, &GPIO_InitStructure);                                                 //根据设定参数初始化GPIOG.0
GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);                                                 //PG.0 输出高

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;                
GPIO_Init(GPIOC, &GPIO_InitStructure);                                                 
GPIO_SetBits(GPIOC,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);    

        
}

/**************************************************************************/
//以下是并口时才开的
//读忙标志,
void RDBF(void)
{
u8 temp;
RS=0; // RS=0
RW=1; // RW=1
delay_us(1);
delay_us(1);
PA(0xFF); //数据线为输入
while(1)
{
E=1;
delay_ms(5);
temp=PAIN;

if ((temp&0x80)==0) break;
}
E=0; // E=0
}
//写数据到指令寄存器
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
//写数据到数据寄存器
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
//初始化LCD-8 位接口
void LCDInit(void)
{ 
REST=1;
delay_ms(10);
REST=0;
delay_ms(10);
REST=1;
delay_ms(10);
WRCommand(0x30); //基本指令集,8 位并行
WRCommand(0x06); //启始点设定：光标右移
WRCommand(0x01); //清除显示DDRAM
WRCommand(0x0C); //显示状态开关：整体显示开，光标显示关，光标显示反白关
WRCommand(0x02); //地址归零
}

//显示数组字符串(显示半宽字型16*8 点阵)
void ShowQQChar(u8 addr,u8 *english,u8 count)
{
u8 i;
WRCommand(addr);//设定DDRAM 地址
for(i=0;i<count;)
{
WRData(english[i*2]);	
WRData(english[i*2+1]);
i++;
}
}

/*//显示数组字符串(显示半宽字型16*8 点阵)
void ShowNUMChar(u8 addr,u8 *english,u8 count)
{
u8 i;
WRCommand(addr);//设定DDRAM 地址
for(i=0;i<count;)
{
WRData(english[i*2]);
i++;
}
}*/

//显示连续字串(半宽字符)
void ShowNUMChar(u8 addr,u8 i,u8 count)
{
u8 j;
for(j=0;j<count;)
{
WRCommand(addr);//设定DDRAM 地址
WRData(i+j);
j++;
WRData(i+j);
addr++;
j++;
}
}

