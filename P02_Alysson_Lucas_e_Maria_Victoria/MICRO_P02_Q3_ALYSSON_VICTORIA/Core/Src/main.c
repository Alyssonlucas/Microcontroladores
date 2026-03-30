/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"
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

  int	contD1=0, contD2=0, contUser=0, faseD4=0;
  int	estado_atual = 0, estado_leds=0;
  int 	sequencia=1;

  while (1)
  {
	  HAL_Delay(100);
	  contD1++; contD2++; contUser++;

	  int SW1 = HAL_GPIO_ReadPin(pino0_GPIO_Port, pino0_Pin);
	  int SW2 = HAL_GPIO_ReadPin(pino1_GPIO_Port, pino1_Pin);

	  if (SW1==GPIO_PIN_RESET && SW2==GPIO_PIN_RESET){
		  estado_atual=0;
	  } else if (SW1==GPIO_PIN_SET && SW2==GPIO_PIN_RESET){
  		  estado_atual=1;
 	  } else if (SW1==GPIO_PIN_RESET && SW2==GPIO_PIN_SET){
	  	  estado_atual=2;
	  } else if (SW1==GPIO_PIN_SET && SW2==GPIO_PIN_SET){
	  	  estado_atual=3;
	  }

	  // 2. A estrutura Switch avalia o valor dessa variável
	  switch (estado_atual){

	  	  case 0:
	  		  if (contD1>=5){
	  			  if (estado_leds == 0) {
	  				  estado_leds = 1; // GPIO_PIN_SET
	  			  } else {
	  				  estado_leds = 0; // GPIO_PIN_RESET
	  			  }
	  			  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, estado_leds);
	  			  HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, estado_leds);
	  			  HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, estado_leds);
	  			  HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, estado_leds);
	  			  contD1=0;
	  		  }
	          break;

	  	case 1:
	  	              // 3. Lógica D1 e D3 arrumada (100ms aceso / 500ms apagado)

	  		if (HAL_GPIO_ReadPin(led1_GPIO_Port, led1_Pin) == GPIO_PIN_RESET){ // Se apagado
                  if (contD1 >= 5) { // Espera 500ms
  	                      HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
  	                      HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
  	                      contD1 = 0;
                  }
            } else { // Se aceso
                  if (contD1 >= 1) { // Espera 100ms
  	                      HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
  	                      HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
  	                      contD1 = 0;
                  }
            }

	         if (contD2 >= 3) {
	  	           HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);
	  	           HAL_GPIO_TogglePin(led4_GPIO_Port, led4_Pin);
	  	           contD2 = 0;
	  	      }
	  	             break;

	  	  case 2:

	  		  if (contD1 >= 5) {

	  			  	// 1. Apaga todo mundo (Garantia de que só um vai ficar aceso)
	  		        HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
	  		        HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
	  		        HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
	  		        HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);

	  		        // 2. Acende o "da vez" e passa a bola pro próximo
	  		        if (sequencia==1) {
	  		            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET); // Acende D1
	  		            sequencia=2; // Prepara o D2 para a próxima rodada
	  		        } else if (sequencia==2) {
	  		            HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET); // Acende D2
	  		            sequencia=3;
	  		        } else if (sequencia==3) {
	  		            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET); // Acende D3
	  		            sequencia=4;
	  		        } else if (sequencia==4) {
	  		            HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET); // Acende D4
	  		            sequencia=1; // Chegou no fim? Volta pro D1!
	  		        }

	  		        // 3. Zera o cronômetro para esperar os próximos 500ms
	  		        contD1 = 0;
	  		  }
	  		  break;

	  	  case 3:
	  	            // Regra inventada por você: Se apertar os dois botões, apaga tudo.
	  	            // O UserLed continua piscando lá embaixo, pois está fora do switch!
	  		  HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
	  	      HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
	  	      HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
	  	      HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);
	  	      break;

	  	  default:
	  	            // Trava de Segurança: se o 'estado_atual' assumir um valor maluco (ex: 5, 10, -1),
	  	            // nós forçamos o sistema a voltar para o estado inicial.
	  	      estado_atual = 0;
	  	      break;
	  	    } // Fim do switch


  	  if (HAL_GPIO_ReadPin(UserLed_GPIO_Port, UserLed_Pin)==GPIO_PIN_SET){
  		  if (contUser>=19){
  			  HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_RESET);
  			  contUser=0;
  		  }
  	  } else{
  		  if (contUser>=1){
  			  HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_SET);
  			  contUser=0;
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
