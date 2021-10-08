#ifndef __LCD12864_H
#define __LCD12864_H         
#include "sys.h"

#define PA(x)     (GPIOA->ODR)=x; //PA0-PA7
#define PAIN      (GPIOA->IDR);

#define REST	PAout(8) 
#define RS 		PCout(13)        
#define RW 		PCout(14)        // PC14        
#define E 		PCout(15)        //  PC15        


void LCD12864IO_Init(void);

void RDBF(void);
void WRCommand(u8 comm);
void WRData(u8 TEMP);
void LCDInit(void);
void ShowQQChar(u8 addr,u8 *english,u8 count);
void ShowNUMChar(u8 addr,u8 i,u8 count);




#endif

