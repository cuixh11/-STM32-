/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();//使能PA端口时钟，该引脚时钟若是不打开，引脚不能使用
  __HAL_RCC_GPIOB_CLK_ENABLE();//使能PB端口时钟

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);//PA.7端口配置，给它高电平，set高电平，reset低电平

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11 
                          |SCK_Pin|DQ_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PA7 ，配置PA.7*/
  GPIO_InitStruct.Pin = GPIO_PIN_7;//PA.7 端口设置
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//推挽输出，IO输出0-接GND， IO输出1 -接VCC，读输入值是未知的。
	/*在STM32中选用IO模式
			 1、浮空输入GPIO_IN_FLOATING ——浮空输入，可以做KEY识别，RX1
       2、带上拉输入GPIO_IPU——IO内部上拉电阻输入
       3、带下拉输入GPIO_IPD—— IO内部下拉电阻输入
       4、模拟输入GPIO_AIN ——应用ADC模拟输入，或者低功耗下省电
       5、开漏输出GPIO_OUT_OD ——IO输出0接GND，IO输出1，悬空，需要外接上拉电阻，才能实现输出高电平。
			 当输出为1时，IO口的状态由上拉电阻拉高电平，但由于是开漏输出模式，这样IO口也就可以由外部电路改变为低电平或不变。
			 可以读IO输入电平变化，实现C51的IO双向功能
       6、推挽输出GPIO_OUT_PP ——IO输出0-接GND， IO输出1 -接VCC，读输入值是未知的
       7、复用功能的推挽输出GPIO_AF_PP ——片内外设功能（I2C的SCL,SDA）
       8、复用功能的开漏输出GPIO_AF_OD——片内外设功能（TX1,MOSI,MISO.SCK.SS）*/
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;//IO口速度频率，高
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);//进行初始化GPIO

  /*Configure GPIO pins : PB0 PB1 PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PBPin */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|DT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = DQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DQ_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
