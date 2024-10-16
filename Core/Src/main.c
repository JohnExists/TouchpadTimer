#include "main.h"

#define OUTPUT 0
#define INPUT 1

ADC_HandleTypeDef hadc1;


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_ADC1_Init();

  launchTimer(&hadc1);
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_A_PIN_TYPE, SEGMENT_A_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_B_PIN_TYPE, SEGMENT_B_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_C_PIN_TYPE, SEGMENT_C_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_D_PIN_TYPE, SEGMENT_D_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_E_PIN_TYPE, SEGMENT_E_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_F_PIN_TYPE, SEGMENT_F_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, SEGMENT_G_PIN_TYPE, SEGMENT_G_PIN_NUMBER, OUTPUT);

	Configure_GPIO_Pins(&GPIO_InitStruct, BUZZER_PIN_TYPE, BUZZER_PIN_NUMBER, OUTPUT);
	Configure_GPIO_Pins(&GPIO_InitStruct, LED_PIN_TYPE, LED_PIN_NUMBER, OUTPUT);



}

/**
 * @brief Configures GPIO pins based on specified parameters.
 *
 * This function configures GPIO pins with the provided configuration settings
 * using the HAL library functions.
 *
 * @param GPIO_InitStruct Pointer to GPIO_InitTypeDef structure
 * containing GPIO configuration.
 * @param pinType Pointer to GPIO port type (e.g., GPIOA, GPIOB).
 * @param pinNumber GPIO pin number to configure (e.g., GPIO_PIN_0, GPIO_PIN_1).
 * @param IO Specifies whether the pin is configured as INPUT or
 * OUTPUT (0 for INPUT, 1 for OUTPUT).
 *
 */
static void Configure_GPIO_Pins(GPIO_InitTypeDef* GPIO_InitStruct, GPIO_TypeDef* pinType, uint32_t pinNumber, int IO)
{
	  GPIO_InitStruct->Pin = pinNumber;
	  GPIO_InitStruct->Mode = (IO == INPUT) ? GPIO_MODE_INPUT : GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct->Pull = (IO == INPUT) ? GPIO_PULLDOWN : GPIO_NOPULL;
	  if(IO == OUTPUT) GPIO_InitStruct->Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(pinType, GPIO_InitStruct);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
