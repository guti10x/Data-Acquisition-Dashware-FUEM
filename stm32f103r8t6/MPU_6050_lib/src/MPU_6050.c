/*
 * MPU_6050.c
 *
 *  Created on: May 1, 2024
 *      Author: Daniel Romero de Ávila - Formula UEM
 */

#include <MPU_6050.h>
#include <main.h>
#include <stdint.h>

extern I2C_HandleTypeDef hi2c1;

void MPU_6050_init(){

	//Inicializamos la configuracion del MPU6050
	 HAL_StatusTypeDef check_connection = HAL_I2C_IsDeviceReady(&hi2c1, (DEVICE_ADDRESS << 1) + 0 , 1, 100); //Status check from the MPU6050

	if (check_connection == HAL_OK){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
	uint8_t gyro_scale = FS_GYRO_500;

	HAL_StatusTypeDef gyro_config = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_CONFIG_GYRO, 1, &gyro_scale, 1, 100); //Gyroscope scale configuration (MAX)

	if (gyro_config == HAL_OK){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_Delay(500);
	}

	uint8_t acc_scale = FS_ACC_4G;

	HAL_StatusTypeDef acc_config =  HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_CONFIG_ACC, 1, &acc_scale, 1, 100); //Accelerometer scale set up (+-4G)

	if (acc_config == HAL_OK){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_Delay(500);
	}

	uint8_t temp_activation = FS_TEMP;

	HAL_StatusTypeDef temp_config =  HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS << 1) + 0, REG_USER_CTRL, 1, &temp_activation, 1, 100); //Disable "Sleep Mode" and enable the internal temperature sensor

	if (temp_config == HAL_OK){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
		HAL_Delay(500);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}

signed short int MPU_6050_Get_Acc_X(){
	uint8_t raw_acc_x[2];
	int16_t acc_x = 0;

	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_READ_ACC_X, 1, raw_acc_x, 2, 100); //Mandamos medir por I2C el registro asociado a las variables de memoria del dato de Aceleracion en X
	acc_x = (((int16_t) raw_acc_x[0] << 8) + raw_acc_x[1]);
    return acc_x;
}

signed short int MPU_6050_Get_Acc_Y(){
	uint8_t raw_acc_y[2];
	int16_t acc_y = 0;

	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_READ_ACC_Y, 1, raw_acc_y, 2, 100); //Mandamos medir por I2C el registro asociado a las variables de memoria del dato de Aceleracion en X
	acc_y = (((int16_t) raw_acc_y[0] << 8) + raw_acc_y[1]);
	return acc_y;
}

signed short int MPU_6050_Get_Acc_Z(){
	uint8_t raw_acc_z[2];
	int16_t acc_z = 0;

	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_READ_ACC_Z, 1, raw_acc_z, 2, 100); //Mandamos medir por I2C el registro asociado a las variables de memoria del dato de Aceleracion en X
	acc_z = (((int16_t) raw_acc_z[0] << 8) + raw_acc_z[1]);
	return acc_z;
}

float MPU_6050_Get_Temp(){
	uint8_t temp_data[2];
	int16_t raw_temp = 0;
	float temp = 0;

	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS << 1) + 1, REG_READ_TEMP, 1, temp_data, 2, 100);
	raw_temp = (temp_data[0] << 8 | temp_data[1]);
	temp = (raw_temp/340.0) + 36.53;
	return temp;
}
