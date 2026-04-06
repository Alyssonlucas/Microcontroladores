/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Questão 2 - Copiando as Configurações de um Projeto para um Novo Projeto
  * @authors        : Alysson Lucas Pontes Cavalcante da Silva e Maria Victória Martins Neves
  * @date           : 25/03/2026
  * @description    : Projeto a partir do anterior, que apenas copiou as
  * 					configurações de placa e periféricos.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	// DEFINIÇÃO DAS VARIÁVEIS LOCAIS (CONTADORES)
	int	contD1=0, contD2=0, contD3=0, contD4=0, contUser=0, faseD4=0;
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
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  // Padroniza a contagem de tempo através do MDC entre os intervalos de tempo
	  HAL_Delay(100);

	  // Incrementa os contadores a cada intervalo de 100ms
	  contD1++;  contD2++;  contD3++;  contUser++;

	  // DEFINIÇÃO DOS INTERVALOS DE TEMPO
	  // Os valores escolhidos devem ser múltiplos de 100ms
	  int timeON_D1 = 5;	// D1: Tempo simétrico para acender e apagar D1
	  int timeOn_D2 = 7, timeOFF_D2 = 3;	// D2: 300 ms apagado, 700 ms aceso
	  int timeOn_D3 = 5, timeOFF_D3 = 4;	// D2: 400 ms apagado, 500 ms aceso
	  int timeOn1_D4 = 10, timeOFF_D4 = 20, timeOn2_D4 = 20;
	  	  	  	  	  	  	  	  	  	  	// D4: 1s aceso, 2s apagado, 2s aceso
	  int timeON_UserLed = 1, timeOFF_UserLed = 19;	// UserLed: 100 ms aceso, 1900 ms apagado

	  // LED 1
	  if (contD1>=timeON_D1){	// Verifica se passou o tempo desejado
		  HAL_GPIO_TogglePin(led1_GPIO_Port, led1_Pin);	// Inverte o valor do D1
		  contD1=0;		// Zera o contador do D1
	  }

	  // LED2
	  if (HAL_GPIO_ReadPin(led2_GPIO_Port, led2_Pin)==GPIO_PIN_RESET){	// Se D2 apagado
		  if (contD2>=timeOFF_D2){	// Verifica se passou o tempo desejado para este caso
			  HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);	// Inverte o valor do D2
			  contD2=0;		// Zera o contador do D2
		  }
	  } else{	// Se D2 aceso
		  if (contD2>=timeOn_D2){	// Verifica se passou o tempo desejado para este caso
			  HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);	// Inverte o valor do D2
			  contD2=0;		// Zera o contador do D2
		  }
	  }

	  // LED 3
	  if (HAL_GPIO_ReadPin(led3_GPIO_Port, led3_Pin) == GPIO_PIN_RESET){ // Se D3 apagado
		  if (contD3>=timeOFF_D3) {	// Verifica se passou o tempo desejado para este caso
			  HAL_GPIO_TogglePin(led3_GPIO_Port, led3_Pin);	// Inverte o valor do D3
			  contD3 = 0;		// Zera o contador do D3
		  }
	  } else{	// Se D3 aceso
		  if (contD3>=timeOn_D3) {	// Verifica se passou o tempo desejado para este caso
				HAL_GPIO_TogglePin(led3_GPIO_Port, led3_Pin);	// Inverte o valor do D3
				contD3 = 0;		// Zera o contador do D3
		  }
	  }

	  // LED 4
	  // o faseD4 funcionará de forma semelhante a uma máquina de estados
	  // Ele fará com que o contador do D4 incremente apenas para os 3 primeiros estados
	  // Após passar por todas as fases, o contador interrompe e o D4 não acende mais
	  if (faseD4<3){
		  contD4++;
	  }

	  if (faseD4==0){	// Primeira fase: D4 acende por 1 segundo
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);	// Acende D4
		  if (contD4>=timeOn1_D4){	// Verifica se passou o tempo desejado para este caso
			  faseD4=1;	// Avança para a próxima fase
			  contD4=0;	// Zera o contador do D4
		  }
	  } else if (faseD4==1){	// Segunda fase: D4 apaga por 2 segundos
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);	// Apaga D4
		  if (contD4>=timeOFF_D4){	// Verifica se passou o tempo desejado para este caso
			  faseD4=2;	// Avança para a próxima fase
			  contD4=0;	// Zera o contador do D4
		  }
	  } else if (faseD4==2){	// Terceira fase: D4 acende por 2 segundos
		  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);	// Acende D4
		  if (contD4>=timeOn2_D4){	// Verifica se passou o tempo desejado para este caso
		  	  faseD4=3;	// Avança para a próxima fase
		  	  	  	  	// Mas não há comando para a próxima fase, então o D4 encerra aqui
		  	  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);	// Apaga D4
		  }
	  }

	  // USERLED
	  if (HAL_GPIO_ReadPin(UserLed_GPIO_Port, UserLed_Pin)==GPIO_PIN_SET){	// Se UserLed apagado
		  if (contUser>=timeOFF_UserLed){	// Verifica se passou o tempo desejado para este caso
			  HAL_GPIO_TogglePin(UserLed_GPIO_Port, UserLed_Pin);	// Acende UserLed
			  contUser=0;	// Zera o contador do UserLed
		  }
	  } else{	// Se UserLed aceso
		  if (contUser>=timeON_UserLed){	// Verifica se passou o tempo desejado para este caso
			  HAL_GPIO_TogglePin(UserLed_GPIO_Port, UserLed_Pin);	// Apaga UserLed
			  contUser=0;	// Zera o contador do UserLed
		  }
	  }

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, led1_Pin|led2_Pin|led3_Pin|led4_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : UserLed_Pin */
  GPIO_InitStruct.Pin = UserLed_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(UserLed_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : pino0_Pin pino1_Pin */
  GPIO_InitStruct.Pin = pino0_Pin|pino1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : led1_Pin led2_Pin led3_Pin led4_Pin */
  GPIO_InitStruct.Pin = led1_Pin|led2_Pin|led3_Pin|led4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
