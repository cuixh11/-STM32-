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
  __HAL_RCC_GPIOA_CLK_ENABLE();//ʹ��PA�˿�ʱ�ӣ�������ʱ�����ǲ��򿪣����Ų���ʹ��
  __HAL_RCC_GPIOB_CLK_ENABLE();//ʹ��PB�˿�ʱ��

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);//PA.7�˿����ã������ߵ�ƽ��set�ߵ�ƽ��reset�͵�ƽ

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_10|GPIO_PIN_11 
                          |SCK_Pin|DQ_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PA7 ������PA.7*/
  GPIO_InitStruct.Pin = GPIO_PIN_7;//PA.7 �˿�����
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;//���������IO���0-��GND�� IO���1 -��VCC��������ֵ��δ֪�ġ�
	/*��STM32��ѡ��IOģʽ
			 1����������GPIO_IN_FLOATING �����������룬������KEYʶ��RX1
       2������������GPIO_IPU����IO�ڲ�������������
       3������������GPIO_IPD���� IO�ڲ�������������
       4��ģ������GPIO_AIN ����Ӧ��ADCģ�����룬���ߵ͹�����ʡ��
       5����©���GPIO_OUT_OD ����IO���0��GND��IO���1�����գ���Ҫ����������裬����ʵ������ߵ�ƽ��
			 �����Ϊ1ʱ��IO�ڵ�״̬�������������ߵ�ƽ���������ǿ�©���ģʽ������IO��Ҳ�Ϳ������ⲿ��·�ı�Ϊ�͵�ƽ�򲻱䡣
			 ���Զ�IO�����ƽ�仯��ʵ��C51��IO˫����
       6���������GPIO_OUT_PP ����IO���0-��GND�� IO���1 -��VCC��������ֵ��δ֪��
       7�����ù��ܵ��������GPIO_AF_PP ����Ƭ�����蹦�ܣ�I2C��SCL,SDA��
       8�����ù��ܵĿ�©���GPIO_AF_OD����Ƭ�����蹦�ܣ�TX1,MOSI,MISO.SCK.SS��*/
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;//IO���ٶ�Ƶ�ʣ���
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);//���г�ʼ��GPIO

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
