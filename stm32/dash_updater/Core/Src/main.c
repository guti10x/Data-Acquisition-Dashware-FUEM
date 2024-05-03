/* USER CODE BEGIN Header */
/**
  **********
  * @file           : main.c
  * @brief          : Main program body
  **********
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  **********
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include <time.h>


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

/* VARIABLES ---------------------------------------------------------*/
// Elementos en la interfaz a modificar en la interfaz si se supera threshold
const char *array_elementos_a_poner_rojo_por_alerta[] = {"speed", "revValue", "gear", "brake1", "brake2", "brake3", "brake4", "voltage","engineTemp",}; //elelementos d el ainterfaz a actualizar por alerta

//Variable para indicar el final del mensaje
uint8_t Cmd_End[3]= {0xff,0xff,0xff};

// Función para actualizar objeto obj de la interfaz con un valor text
void NEXTION_SendText(char *obj, char *text, char *units) {

	uint8_t *buffer = malloc(50 * sizeof(char)); // Reserva memoria para un buffer de 50 bytes

	int len = 0;

	if (units == NULL || units[0] == '\0') {
		len = sprintf((char *)buffer, "%s.txt=\"%s\"", obj, text);  // Agregar el texto al objeto

	}else {
		len = sprintf((char *)buffer, "%s.txt=\"%s%s\"", obj, text, units); // Agrega las unidades al texto del objeto
	}

    HAL_UART_Transmit(&huart1, buffer, len, 1000); // Transmite el buffer a través de UART
    HAL_UART_Transmit(&huart1, Cmd_End, 3, 100); // Transmite Cmd_End para indicar que finalizó el mensaje
    free(buffer); // Libera la memoria asignada al buffer
}

// Para baras laterales de frenado y aceleración + barra superiro de revoluciones
void NEXTION_SendNumber(char *obj, int number) {
    uint8_t *buffer = malloc(50 * sizeof(char)); // Reserva memoria para un buffer de 50 bytes
    int len = sprintf((char *)buffer, "%s.val=%d", obj, number); // Inicializa el buffer con el objeto y el valor a inicializar
    HAL_UART_Transmit(&huart1, buffer, len, 1000); // Transmite el buffer a través de UART
    HAL_UART_Transmit(&huart1, Cmd_End, 3, 100); // Transmite Cmd_End para indicar que finalizó el mensaje
    free(buffer); // Libera la memoria asignada al buffer
}

void NEXTION_Alert(int color) {

	uint8_t *buffer = malloc(50 * sizeof(char));

    for (int i = 0; i < 9; i++) {

        // Formatea y transmite el mensaje para el elemento actual
        int len = sprintf((char *)buffer, "%s.bco=%d", array_elementos_a_poner_rojo_por_alerta[i], color);

        HAL_UART_Transmit(&huart1, buffer, len, 1000);
        HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);

        // Libera el buffer
        free(buffer);
    }
}


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
        	NEXTION_SendText("speed", text, NULL);

            break;
        case 0x120:
        	NEXTION_SendText("voltage", text, "V");
        	if (random_value < 85 && random_value > 0) {
        	    NEXTION_Alert(0);
        	} else if (random_value < 98) {
        	    NEXTION_Alert(63488);
        	}
            break;
        case 0x655:
        	NEXTION_SendNumber("brakePedal", random_value);
            break;
        case 0x640:
        	NEXTION_SendText("revValue", text, " RPM");
            break;
        case 0x641:
        	NEXTION_SendText("gear", text, NULL);
            break;
        case 0x642:
        	NEXTION_SendNumber("acePedal", random_value);
            break;
        case 0x643:
        	NEXTION_SendText("brake1", text, "\xB0");
            break;
        case 0x644:
        	NEXTION_SendText("brake2", text, "\xB0");
            break;
        case 0x645:
        	NEXTION_SendText("brake3", text, "\xB0");
            break;
        case 0x646:
        	NEXTION_SendText("brake4", text, "\xB0");
            break;
        case 0x647:
        	NEXTION_SendText("engineTemp", text, "\xB0");
        	if (random_value < 85 && random_value > 0) {
        	    NEXTION_Alert(0);
        	} else if (random_value < 98) {
        	    NEXTION_Alert(63488);
        	}
            break;
            break;
        case 0x648:
        	ledsRevoluciones(rev);
            break;
        default:
            break;
    }
}

void ledsRevoluciones(int val) {
    int resultado1 = 0;
    int resultado2 = 0;
    int resultado3 = 0;

    if (val >= 0 && val < 3000) {
        resultado1 = val / 30.0; // Rango 0-3000
        resultado1 = (resultado1 + 10) / 20 * 20;
        resultado2 = 0;
        resultado3 = 0;
    } else if (val >= 3000 && val < 6000) {
        resultado1 = 100;
        resultado2 = (val - 3000) / 30.0; // Rango 3000-6000
        resultado2 = (resultado2 + 10) / 20 * 20;

        resultado3 = 0;
    } else if (val >= 6000 && val <= 9000) {
        resultado1 = 100;
        resultado2 = 100;
        resultado3 = (val - 6000) / 30.0; // Rango 6000-9000
        resultado3 = (resultado3 + 10) / 20 * 20;

    }

    // Envía los resultados a las barras correspondientes
    NEXTION_SendNumber("led1", resultado1);
    NEXTION_SendNumber("led2", resultado2);
    NEXTION_SendNumber("led3", resultado3);
}

void NEXTION_SendPageChange(char *page_name) {
    // Reserva memoria para un buffer de 50 bytes
    uint8_t *buffer = malloc(50 * sizeof(char));
    // Inicializa el buffer con la instrucción para cambiar de página
    int len = sprintf((char *)buffer, "page %s", page_name);
    // Transmite el buffer a través de UART
    HAL_UART_Transmit(&huart1, buffer, len, 1000);
    // Transmite un comando para indicar el final del mensaje
    HAL_UART_Transmit(&huart1, Cmd_End, 3, 100);
    // Libera la memoria asignada al buffer
    free(buffer);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  // Semilla para la generación de números aleatorios
  srand(time(NULL));

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();

  NEXTION_SendPageChange("page0");
  HAL_Delay(2800);

  NEXTION_SendPageChange("page1");

  //Inicializar interfaz a negro (por si se quedó con estilos a rojo por NEXTION_Alert())
  NEXTION_Alert(0);

  /* Infinite loop */
  while (1)
  {
	int randoom_value = 2;
	char text[20]; // Debes asegurarte de que el tamaño sea suficiente para almacenar el texto
	sprintf(text, "%d", randoom_value);

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
  huart1.Init.BaudRate = 9600;
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
