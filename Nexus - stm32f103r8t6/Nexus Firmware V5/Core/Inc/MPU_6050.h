/*
 * MPU_6050.h
 *
 *  Created on: May 1, 2024
 *      Author: danie
 */

#ifndef INC_MPU_6050_H_
#define INC_MPU_6050_H_

#define DEVICE_ADDRESS 0x68

#define REG_CONFIG_GYRO 27
#define REG_CONFIG_ACC 28
#define REG_USER_CTRL 107
#define REG_DATA 59

#define FS_GYRO_250 0
#define FS_GYRO_500 8
#define FS_GYRO_1000 9
#define FS_GYRO_2000 10

#define FS_ACC_2G 0
#define FS_ACC_4G 8
#define FS_ACC_8G 9
#define FS_ACC_16G 10

#define FS_TEMP 0

#define REG_READ_ACC_X 59
#define REG_READ_ACC_Y 61
#define REG_READ_ACC_Z 63

#define REG_READ_TEMP 65

void MPU_6050_init();

signed short int MPU_6050_Get_Acc_X();
signed short int MPU_6050_Get_Acc_Y();
signed short int MPU_6050_Get_Acc_Z();

float MPU_6050_Get_Temp();

#endif /* INC_MPU_6050_H_ */
