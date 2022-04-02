#ifndef __XIANSHISPI_H__
#define __XIANSHISPI_H__

#include "main.h"

#define OLED_DC(a)  if(a){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);}\
                     else {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);}
										 
#define OLED_CS(a)  if(a){HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);}\
                     else {HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);}	

#define OLED_SCL(a) if(a){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET);}\
                     else {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET);}		

#define OLED_SDIN(a) 	if(a){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET);}\
                     else {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET);}			

#define OLED_RST(a)	if(a){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);}\
                     else {HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);}									 

#define OLED_CMD  0	
#define OLED_DATA 1	
#define OLED_MODE 0										 


#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64		

void OLED_Init(void);
//void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char *p);
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char z,unsigned char no,unsigned char no1);
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char no);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned int chr);
//void OLED_Clear2(void)  ;
//void OLED_ShowChar111(unsigned char x,unsigned char y,unsigned int chr);
void OLED_Clear(void);
void OLED_Set_Pos(unsigned char x, unsigned char y) ;
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);
										 
#endif
