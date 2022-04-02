/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "xianshispi.h"
#include "ds18b20.h"//�¶ȴ�����
#include "HK711.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define k1 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_12)//�������������Ķ˿�
#define k2 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_13)
#define k3 HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_14)

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
ulong adc_bit,adc_cs;	//�����������������������adֵ�����ʱ��adֵ
uchar temp;						//���������¶�
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void SystemClock_Config(void);//ϵͳʱ�ӳ�ʼ��
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
  * @brief The measured data is displayed on the display screen
  * @retval None
  */
void xianshi()									//��ʾ������ʾ��õ�����
{
	OLED_ShowCHinese(32, 0,4,0,1);	//��ʾ�����֡�����ϵͳ������һ����X��λ�ã��ڶ�����Y��λ�ã�//����������ʾ�ֵĸ��������ĸ��������ֿ��е�λ�ã����������
	
/* ��ʾDTʵʱ�⵽���������� */		
	OLED_ShowCHinese(0,  2,2,4,1);	//��ʾ�����֡�������,F8X16[]��ռ2ҳ
	OLED_ShowChar(32,    2,':');			//��ʾð�ţ�
	OLED_ShowChar(32+8,  2,adc_bit/1000%10+'0');	//ǧλ
	OLED_ShowChar(32+8*2,2,adc_bit/100%10+'0');		//��λ
	OLED_ShowChar(32+8*3,2,adc_bit/10%10+'0');		//ʮλ
	OLED_ShowChar(32+8*4,2,adc_bit/1%10+'0');			//��λ
	OLED_ShowChar(32+8*5,2,'g');//��ʾ�ˡ�g��
	
/* ��ʾDS18B20ʵʱ�⵽���¶����� */		
	OLED_ShowCHinese(0,4,2,6,1);//��ʾ�����֡��¶ȡ�
	OLED_ShowChar(32,	 4,':');//��ʾð�ţ�
	OLED_ShowChar(32+8,4,temp/10%10+'0');
	OLED_ShowChar(32+8*2,4,temp/1%10+'0');
	OLED_ShowChar(32+8*3,4,'C');//��ʾ�¶ȵ�λ��C�����������϶ȡ�
}

/* USER CODE END 0 */


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)//������
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();//IO��ʼ��
	
  MX_TIM2_Init();//ʱ�ӳ�ʼ��
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

	OLED_Init();//��ʾ����ʼ��
	
	adc_cs=read_ad();//��ȡ���γ��ش�������ֵ�����ڵ������
	adc_cs=adc_cs/10000;		
	adc_cs=read_ad();
	adc_cs=adc_cs/10000;
	adc_cs=read_ad();
	adc_cs=adc_cs/10000;

  /* USER CODE END 2 */

 

  while (1)//һֱѭ�����г��ش������ĳ��򣬶�ȡ��õ��������͵���Ӧ������
  {
	adc_bit=read_ad();
	adc_bit=adc_bit/10000;		//��long �ͱ����������ʺʹ�ſռ�ռ����Դ̫�࣬�̳���100������Ϊint �ͣ�,ǿ������ת�����ں������㡣
	adc_bit=adc_bit-adc_cs;
	adc_bit=adc_bit*20;
	
	if(adc_bit>9000){adc_bit=0;}//���ݵ���ʾ��λ�����ݳ���9000�Ͳ������ϼ�
	
	temp=caozuo();//���¶ȣ����¶ȴ��¶ȴ������϶�ȡ��Ȼ����á�xianshi����ʾ�����ĳ���
	
	xianshi();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		{
			Error_Handler();
		}
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
		{
			Error_Handler();
		}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
