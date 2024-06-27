/*
 * nextion_comunication.h
 *
 *  Created on: June 1, 2024
 *      Author: Daniel Gutiérrez Torres - Formula UEM
*/

#ifndef NEXTION_COMMUNICATION_H
#define NEXTION_COMMUNICATION_H

#include "stm32f1xx_hal.h"

/* VARIABLES ---------------------------------------------------------*/
// Elementos en la interfaz a modificar en la interfaz si se supera threshold
//Variable para indicar el final del mensaje
extern const char *array_elementos_a_poner_rojo_por_alerta[];
extern const uint8_t Cmd_End[3];



/* FUNCIONES ---------------------------------------------------------*/

// Función para enviar texto a un objeto de la interfaz
void NEXTION_SendText(UART_HandleTypeDef *huart, char *obj, char *text, char *units);
void NEXTION_SendNumber(UART_HandleTypeDef *huart, char *obj, int number);
void NEXTION_Send_Revs(UART_HandleTypeDef *huart, int val);
void NEXTION_SendPageChange(UART_HandleTypeDef *huart, char *page_name);
void NEXTION_Alert(UART_HandleTypeDef *huart, int color);
void NEXTION_estado_color(UART_HandleTypeDef *huart, char *obj, int color);

#endif // NEXTION_COMMUNICATION_H
