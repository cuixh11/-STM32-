#ifndef __HK711_H__
#define __HK711_H__

#include "main.h"


#define scl(a) if(a){HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);}else{HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);}//定义压力传感器的控制端口
#define dt HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8)//压力传感器的数据输出端口

unsigned long read_ad(void);

#endif
