#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "main.h"
#define DQ(n)   if(n){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);}\
												else{HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);}												
#define read_ds18b20 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9)												
void yanshi_dq(uint32_t i);
uchar read(void);
void write(uint dat);
void int_ic(void);
uchar caozuo(void);
#endif
												