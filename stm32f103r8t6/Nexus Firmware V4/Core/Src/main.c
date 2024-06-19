/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"

#include "MPU_6050.h"

/* Connectivity variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart3;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART3_UART_Init(void);

/* Private user code ---------------------------------------------------------*/

// Configuración de CAN
CAN_TxHeaderTypeDef TxHeader;  // Configuración parámetros del mensaje CAN a transmitir
CAN_RxHeaderTypeDef RxHeader;  // Configuración parámetros del mensaje CAN a recibir
uint32_t TxMailbox;  // Variable para almacenar el identificador del mailbox utilizado para la transmisión de mensajes CAN
uint8_t TxData[8];   // Variable para almacenar datos a transmitir por CAN
uint8_t RxData[8];   // Variable para almacenar datos recibidos por CAN
uint8_t RxFlag118 = 0;  // Indicar recepción de mensaje CAN con id 0x118
uint8_t RxFlag649 = 0;  // Indicar recepción de mensaje CAN con id 0x649
uint8_t Id = 0;  // Identificador para diferenciar mensajes
uint8_t countNex = 0;  // Contador

// Datos del acelerómetro
int16_t acc_x;  // Valor bruto del acelerómetro en el eje x
int16_t acc_y;  // Valor bruto del acelerómetro en el eje y
int16_t acc_z;  // Valor bruto del acelerómetro en el eje z
float x_acceleration;  // Valor calculado de la aceleración en el eje x
float y_acceleration;  // Valor calculado de la aceleración en el eje y
float z_acceleration;  // Valor calculado de la aceleración en el eje z
uint8_t acx_data[2];  // aceleración en el eje x en formato texto
uint8_t acy_data[2];  // Aceleración en el eje y en formato texto
uint8_t acz_data[2];  // Aceleración en el eje z en formato texto

// Datos de temperatura
int16_t raw_temp;  // Valor bruto de la temperatura
float temp;  // Valor calculado de la temperatura
uint8_t temp_data[2];  // temperatura en formato texto

// Datos del motor y vehículo
uint8_t Engine_Speed = 0;  // Velocidad del motor
uint8_t Throttle_Pos = 0;  // Posición del acelerador
uint8_t Coolant_Temp = 0;  // Temperatura del refrigerante
uint8_t Battery_Voltage = 0;  // Voltaje batería
uint8_t Throttle_Pedal = 0;  // Pedal acelerador
int16_t Brake_Pressure = 0;  // Pedal freno
int16_t RPM = 0;  // Revoluciones por minuto
uint8_t gear = 0b00000000;  // Marcha

// Textos para mostrar datos
char RPM_text[20];  // Texto con valor de RPM
char Coolant_Text[20];  // Texto con valor de temperatura del refrigerante
char Battery_Text[20];  // Texto con valor de voltaje de la batería

// Función para manejar la recepción de mensajes en el FIFO
// (Se activa automáticamente cuando se detecta que hay un mensaje pendiente en el FIFO)
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	countNex++;

	switch (RxHeader.StdId){

		case 0x118:
			// Temperatura del mortor
			Engine_Speed = (uint8_t)RxData[0];
			sprintf(RPM_text, "%d", Engine_Speed*100);
			//NEXTION_SendText("revValue",RPM_text ," RPM");
			//NEXTION_Send_Revs(Engine_Speed*100);

			// Pedal de aceleración
			Throttle_Pos = (uint8_t)RxData[1];
			//NEXTION_SendNumber("acePedal", Throttle_Pos);

			// Temperatura del motor
			Coolant_Temp = (uint8_t)RxData[3];
			//sprintf(Coolant_Text, "%d", Coolant_Temp);
			//NEXTION_SendText_unidades("engineTemp",Coolant_Text ,"\xB0");
			break;

		case 0x120:
			// Voltaje de la batería
			Battery_Voltage = (uint8_t)RxData[3];
			//sprintf(Battery_Text, "%d", Battery_Voltage);
			//NEXTION_SendText("voltage", Battery_Text, "V");

			break;
		case 0x655:
			//Pedal de freno
			Brake_Pressure = (int16_t)RxData[0]<<8 | RxData[1];
			//NEXTION_SendNumber("brakePedal", Brake_Pressure/100);

			break;
		case 0x640:
			// Revoluciones por minuto
			RPM = (int16_t)RxData[0]<<8 | RxData[1];
			break;
	}
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void){

  /* MCU Configuration--------------------------------------------------------*/
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();

  //Inicializa comunicación CAN
  HAL_CAN_Start(&hcan);

  // Activar notificaciones para manejar interrupciones cuando hay mensajes pendientes en el FIFO0 de recepción del controlador CAN
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

  // Inicializa el sensor MPU-6050
  MPU_6050_init();

  // Configuración de los parámetros de envío CAN
  TxHeader.StdId = 0x446;
  TxHeader.ExtId = 0x00;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.DLC = 4;
  TxHeader.TransmitGlobalTime = DISABLE;
  /* USER CODE BEGIN WHILE */
  while (1) {

	  // Lectura de datos del sensor MPU-6050
	  x_acceleration = MPU_6050_Get_Acc_X();
	  x_acceleration = x_acceleration / 1000;

	  y_acceleration = MPU_6050_Get_Acc_Y();
	  y_acceleration = y_acceleration / 1000;

	  z_acceleration = MPU_6050_Get_Acc_Z();
	  z_acceleration = z_acceleration / 1000;

	  // Lectura sensor temperatura
	  temp = MPU_6050_Get_Temp();

	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
	  HAL_Delay(50);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 4;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
