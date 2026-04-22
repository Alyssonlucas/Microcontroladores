/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Questão 1 - Foregroung-Background + Superloop modularizado
  * @author         : Alysson Lucas Pontes Cavalcante da Silva e Maria Victória Martins Neves
  * @date           : 13/04/2026
  * @details        : Reestruturar a questão 4 do projeto 2 com funções e ponteiros
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

/* Prototipação das funções criadas */
void Ler_Botoes(int *estado_atual);
void Verificar_Mudanca_Estado(int estado_atual, int *estado_anterior, int *sequencia, int *estado_leds);
void Estado_0(uint32_t tempo_atual, uint32_t *timeON_0, int *estado_leds);
void Estado_1(uint32_t tempo_atual, uint32_t *timeD1_1, uint32_t *timeON_D2_1);
void Estado_2(uint32_t tempo_atual, uint32_t *tempo500, int *sequencia);
void Estado_3(void);
void UserLed(uint32_t tempo_atual, uint32_t *time_UserLed);

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

	// DEFINIÇÃO DE VARIÁVEIS LOCAIS (Ficam na stack da main)
	uint32_t tempo_atual = HAL_GetTick();

	// Variáveis para salvar os tempos
	uint32_t timeON_0 = tempo_atual;
	uint32_t timeD1_1 = tempo_atual;
    uint32_t timeON_D2_1 = tempo_atual;
	uint32_t tempo500 = tempo_atual;
	uint32_t time_UserLed = tempo_atual;

	// Variáveis para salvar os estados
	int	estado_atual = 0;
    int estado_anterior = 0;
    int estado_leds = 0;
	int	sequencia = 1;	// Auxiliar para o terceiro caso

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
	  // Atualiza o tempo atual em milissegundos
	  tempo_atual = HAL_GetTick();

	  // 1. Identificação do estado (passando o endereço de estado_atual)
	  Ler_Botoes(&estado_atual);

	  // 2. Reinício do sistema caso o estado mude
	  Verificar_Mudanca_Estado(estado_atual, &estado_anterior, &sequencia, &estado_leds);

	  // 3. Máquina de Estados (Delay Não Blocante)
	  switch (estado_atual) //Poderia ter sido colocado como uma função
      {
          case 0:
              Estado_0(tempo_atual, &timeON_0, &estado_leds);
              break;

          case 1:
              Estado_1(tempo_atual, &timeD1_1, &timeON_D2_1);
              break;

          case 2:
              Estado_2(tempo_atual, &tempo500, &sequencia);
              break;

          case 3:
              Estado_3();
              break;

          default:
              estado_atual = 0;
              break;
	  }

	  // 4. Controle independente do LED da placa
	  UserLed(tempo_atual, &time_UserLed);

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

/**
 * @brief Lê os botões e atualiza o estado atual do sistema via ponteiro.
 * @param estado_atual Ponteiro para a variável que guarda o estado.
 */
void Ler_Botoes(int *estado_atual)
{
    int SW1 = HAL_GPIO_ReadPin(pino0_GPIO_Port, pino0_Pin);
    int SW2 = HAL_GPIO_ReadPin(pino1_GPIO_Port, pino1_Pin);

    if (SW1 == GPIO_PIN_SET && SW2 == GPIO_PIN_SET) {
        *estado_atual = 0;
    } else if (SW1 == GPIO_PIN_RESET && SW2 == GPIO_PIN_SET) {
        *estado_atual = 1;
    } else if (SW1 == GPIO_PIN_SET && SW2 == GPIO_PIN_RESET) {
        *estado_atual = 2;
    } else if (SW1 == GPIO_PIN_RESET && SW2 == GPIO_PIN_RESET) {
        *estado_atual = 3;
    }
}

/**
 * @brief Verifica se houve mudança de estado para reiniciar variáveis de controle.
 * @param estado_atual Valor atual do estado.
 * @param estado_anterior Ponteiro para atualizar o último estado registrado.
 * @param sequencia Ponteiro para a sequência do caso 2.
 * @param estado_leds Ponteiro para resetar o status lógico dos LEDs.
 */
void Verificar_Mudanca_Estado(int estado_atual, int *estado_anterior, int *sequencia, int *estado_leds)
{
    if (estado_atual != *estado_anterior) {
        *sequencia = 1;
        *estado_leds = 0;

        // Apaga todos os LEDs
        HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);

        *estado_anterior = estado_atual;
    }
}

/**
 * @brief Lógica do Estado 0 (Pisca todos a cada 500ms).
 */
void Estado_0(uint32_t tempo_atual, uint32_t *timeON_0, int *estado_leds)
{
    if ((tempo_atual - *timeON_0) >= 500) {
        if (*estado_leds == 0) {
            *estado_leds = 1;
        } else {
            *estado_leds = 0;
        }

        HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, *estado_leds);
        HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, *estado_leds);
        HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, *estado_leds);
        HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, *estado_leds);

        *timeON_0 = tempo_atual;
    }
}

/**
 * @brief Lógica do Estado 1 (Padrões assimétricos e simétricos).
 */
void Estado_1(uint32_t tempo_atual, uint32_t *timeD1_1, uint32_t *timeON_D2_1)
{
    // LEDs 1 e 3: 100 ms acesos, 500 ms apagados
    if (HAL_GPIO_ReadPin(led1_GPIO_Port, led1_Pin) == GPIO_PIN_SET) { // Se apagados
        if ((tempo_atual - *timeD1_1) >= 500) {
            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
            *timeD1_1 = tempo_atual;
        }
    } else { // Se acesos
        if ((tempo_atual - *timeD1_1) >= 100) {
            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
            *timeD1_1 = tempo_atual;
        }
    }

    // LEDs 2 e 4: 300 ms acesos, 300 ms apagados
    if ((tempo_atual - *timeON_D2_1) >= 300) {
        HAL_GPIO_TogglePin(led2_GPIO_Port, led2_Pin);
        HAL_GPIO_TogglePin(led4_GPIO_Port, led4_Pin);
        *timeON_D2_1 = tempo_atual;
    }
}

/**
 * @brief Lógica do Estado 2 (Sequência D1->D2->D3->D4).
 */
void Estado_2(uint32_t tempo_atual, uint32_t *tempo500, int *sequencia)
{
    if ((tempo_atual - *tempo500) >= 500) {
        if (*sequencia == 1) {
            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);
            *sequencia = 2;
        } else if (*sequencia == 2) {
            HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);
            *sequencia = 3;
        } else if (*sequencia == 3) {
            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_SET);
            *sequencia = 4;
        } else if (*sequencia == 4) {
            HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_SET);
            *sequencia = 1;
        }
        *tempo500 = tempo_atual;
    }
}

/**
 * @brief Lógica do Estado 3 (Todos acesos).
 */
void Estado_3(void)
{
    HAL_GPIO_WritePin(led1_GPIO_Port, led1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led2_GPIO_Port, led2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led3_GPIO_Port, led3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(led4_GPIO_Port, led4_Pin, GPIO_PIN_RESET);
}

/**
 * @brief Controla o pisca do LED da placa de forma assíncrona.
 */
void UserLed(uint32_t tempo_atual, uint32_t *time_UserLed)
{
    if (HAL_GPIO_ReadPin(UserLed_GPIO_Port, UserLed_Pin) == GPIO_PIN_SET) { // Se apagado
        if ((tempo_atual - *time_UserLed) >= 1900) {
            HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_RESET);
            *time_UserLed = tempo_atual;
        }
    } else { // Se aceso
        if ((tempo_atual - *time_UserLed) >= 100) {
            HAL_GPIO_WritePin(UserLed_GPIO_Port, UserLed_Pin, GPIO_PIN_SET);
            *time_UserLed = tempo_atual;
        }
    }
}

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
  * where the assert_param error has occurred.
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
