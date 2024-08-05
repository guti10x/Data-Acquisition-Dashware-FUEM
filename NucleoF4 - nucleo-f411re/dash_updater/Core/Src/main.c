/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include <time.h>
#include "nextion_comunication.h"

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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void procesarReceivedCan(uint16_t valor) {
    // Generar un número aleatorio entre 0 y 9
    int random_value = rand() % 100;
    int rev = rand() % 9000;

    char text[4]; // Suponiendo que los valores aleatorios solo van de 0 a 9
    sprintf(text, "%d", random_value);

    // Añadir un retraso de 10ms
    HAL_Delay(10);

    switch(valor) {
        case 0x110:
        	NEXTION_SendText(&huart1,"speed", text, NULL);

            break;
        case 0x120:
        	NEXTION_SendText(&huart1,"voltage", text, "V");
        	if (random_value > 0 && random_value <= 50) {
        	    NEXTION_Alert(&huart1, 0); //black
        	    NEXTION_estado_color(&huart1, "voltage", 36609);  //green-
        	} else if (random_value > 50 && random_value <= 80) {
        	    NEXTION_Alert(&huart1, 0); //black
        	    NEXTION_estado_color(&huart1, "voltage", 64520); //orange
        	} else if (random_value > 91) {
        	    NEXTION_Alert(&huart1, 63488); // red
        	    NEXTION_estado_color(&huart1, "voltage", 63488); //red
        	}

            break;

        case 0x655:
        	NEXTION_SendNumber(&huart1, "brakePedal", random_value);
            break;
        case 0x640:
        	strcpy(text, "2");
        	NEXTION_SendText(&huart1,"revValue", "car", " RPM");
            break;
        case 0x641:
        	NEXTION_SendText(&huart1,"gear", text, NULL);
            break;
        case 0x642:
        	NEXTION_SendNumber(&huart1, "acePedal", random_value);
            break;
        case 0x643:
        	NEXTION_SendText(&huart1,"brake1", text, "\xB0");
            break;
        case 0x644:
        	NEXTION_SendText(&huart1,"brake2", text, "\xB0");
            break;
        case 0x645:
        	NEXTION_SendText(&huart1,"brake3", text, "\xB0");
            break;
        case 0x646:
        	NEXTION_SendText(&huart1,"brake4", text, "\xB0");
            break;
        case 0x647:
        	NEXTION_SendText(&huart1,"engineTemp", text, "\xB0");
        	if (random_value > 0 && random_value <= 50) {
        	    NEXTION_Alert(&huart1,0); //black
        	    NEXTION_estado_color(&huart1, "engineTemp", 36609);  //green
        	} else if (random_value > 50 && random_value <= 80) {
        	    NEXTION_Alert(&huart1,0);
        	    NEXTION_estado_color(&huart1, "engineTemp", 64520); //orange
        	} else if (random_value > 91) {
        	    NEXTION_Alert(&huart1,63488); // red
        	    NEXTION_estado_color(&huart1, "engineTemp", 63488); // red
        	}

			break;

        case 0x648:
        	NEXTION_Send_Revs_v2(&huart1, rev);
            break;
        default:
            break;
    }
}
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
    // Semilla para la generación de números aleatorios
    srand(time(NULL));
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //Mostrar landing view
  //NEXTION_SendPageChange(&huart1,"page0");
  //HAL_Delay(2800);
  //Mostrar dash view
  //NEXTION_SendPageChange(&huart1,"page2");
  HAL_Delay(3400);
  //Mostrar dash view
  //NEXTION_SendPageChange(&huart1,"page3");
  //HAL_Delay(2800);
  //Mostrar dash view
  NEXTION_SendPageChange(&huart1,"page1");

  //Inicializar interfaz a negro (por si se quedó con estilos a rojo por NEXTION_Alert())
  NEXTION_Alert(&huart1, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  	//HAL_Delay(400);
	  	int randoom_value = 2;
	  	char text[20]; // Declarar variable donde alamcenar la conversión
	  	sprintf(text, "%d", randoom_value); //Inicializar la conversión

	  	// Generar valor aleatorio entre 0 y 9
	  	int random_value = rand() % 12;

	  	switch(random_value) {
	  		case 0:
	  			procesarReceivedCan(0x110);
	  			break;
	  		case 1:
	  			procesarReceivedCan(0x120);
	  			break;
	  		case 2:
	  			procesarReceivedCan(0x655);
	  			break;
	  		case 3:
	  			procesarReceivedCan(0x640);
	  			break;
	  		case 4:
	  			procesarReceivedCan(0x641);
	  			break;
	  		case 5:
	  			procesarReceivedCan(0x642);
	  			break;
	  		case 6:
	  			procesarReceivedCan(0x643);
	  			break;
	  		case 7:
	  			procesarReceivedCan(0x644);
	  			break;
	  		case 8:
	  			procesarReceivedCan(0x645);
	  			break;
	  		case 9:
	  			procesarReceivedCan(0x646);
	  			break;
	  		case 10:
	  			procesarReceivedCan(0x647);
	  			break;
	  		case 11:
	  			procesarReceivedCan(0x648);
	  			break;
	  		default:
	  			printf("Número aleatorio fuera de rango\n");
	  			break;
	  	}

	}

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

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
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

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
