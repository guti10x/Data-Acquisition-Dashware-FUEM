#include "nextion_comunication.h"
#include <stdlib.h>
#include <stdio.h>

/* VARIABLES ---------------------------------------------------------*/
// Elementos en la interfaz a modificar en la interfaz si se supera threshold
//elelementos d el ainterfaz a actualizar por alerta
//Variable para indicar el final del mensaje
const char *array_elementos_a_poner_rojo_por_alerta[] = {"speed", "revValue", "gear", "brake1", "brake2", "brake3", "brake4"};
const uint8_t Cmd_End[3] = {0xff, 0xff, 0xff};


// Función para actualizar objeto obj de la interfaz con un valor text
void NEXTION_SendText(UART_HandleTypeDef *huart, char *obj, char *text, char *units) {
    uint8_t *buffer = malloc(50 * sizeof(char)); // Reserva memoria para un buffer de 50 bytes
    int len = 0;

    if (units == NULL || units[0] == '\0') {
        len = sprintf((char *)buffer, "%s.txt=\"%s\"", obj, text);  // Agregar el texto al objeto
    } else {
        len = sprintf((char *)buffer, "%s.txt=\"%s%s\"", obj, text, units); // Agrega las unidades al texto del objeto
    }

    HAL_UART_Transmit(huart, buffer, len, 1000); // Transmite el buffer a través de UART
    HAL_UART_Transmit(huart, Cmd_End, 3, 100); // Transmite Cmd_End para indicar que finalizó el mensaje
    free(buffer); // Libera la memoria asignada al buffer
}

// Actualiza valores de las barras de frenado, aceleración y revoluciones
void NEXTION_SendNumber(UART_HandleTypeDef *huart, char *obj, int number) {
    uint8_t *buffer = malloc(50 * sizeof(char)); // Reserva memoria para un buffer de 50 bytes
    int len = sprintf((char *)buffer, "%s.val=%d", obj, number); // Inicializa el buffer con el objeto y el valor a inicializar
    HAL_UART_Transmit(huart, buffer, len, 1000); // Transmite el buffer a través de UART
    HAL_UART_Transmit(huart, Cmd_End, 3, 100); // Transmite Cmd_End para indicar que finalizó el mensaje
    free(buffer); // Libera la memoria asignada al buffer
}

// Función para actualizar los indicadores de revoluviones del dash (progress bar)
void NEXTION_Send_Revs(UART_HandleTypeDef *huart, int val) {
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
    NEXTION_SendNumber(huart,"led1", resultado1);
    NEXTION_SendNumber(huart,"led2", resultado2);
    NEXTION_SendNumber(huart,"led3", resultado3);
}

//Función para realizar la transicción de la landing view al dash
void NEXTION_SendPageChange(UART_HandleTypeDef *huart,char *page_name) {
    // Reserva memoria para un buffer de 50 bytes
    uint8_t *buffer = malloc(50 * sizeof(char));
    // Inicializa el buffer con la instrucción para cambiar de página
    int len = sprintf((char *)buffer, "page %s", page_name);
    // Transmite el buffer a través de UART
    HAL_UART_Transmit(huart, buffer, len, 1000);
    // Transmite un comando para indicar el final del mensaje
    HAL_UART_Transmit(huart, Cmd_End, 3, 100);
    // Libera la memoria asignada al buffer
    free(buffer);
}

//Función para actualizar todos los colores de los elementos a rojo por temperatura del motor o voltaje bateria elevados
void NEXTION_Alert(UART_HandleTypeDef *huart,int color) {

	uint8_t *buffer = malloc(50 * sizeof(char));

    for (int i = 0; i < 7; i++) {

        // Formatea y transmite el mensaje para el elemento actual
        int len = sprintf((char *)buffer, "%s.bco=%d", array_elementos_a_poner_rojo_por_alerta[i], color);

        HAL_UART_Transmit(huart, buffer, len, 1000);
        HAL_UART_Transmit(huart, Cmd_End, 3, 100);

        // Libera el buffer
        free(buffer);
    }
}

//Función para actualizar color estado de voltaje bateria y temperatura del motor
void NEXTION_estado_color(UART_HandleTypeDef *huart, char *obj, int color) {

	uint8_t *buffer = malloc(50 * sizeof(char));

	// Formatea y transmite el mensaje para el elemento actual
	int len = sprintf((char *)buffer, "%s.bco=%d", obj, color);

    HAL_UART_Transmit(huart, buffer, len, 1000);
    HAL_UART_Transmit(huart, Cmd_End, 3, 100);

    // Libera el buffer
    free(buffer);
}

// Función para actualizar los indicadores de revoluviones del dash (rectángulos de colores)
void NEXTION_Send_Revs_v2(UART_HandleTypeDef *huart, int val) {
    int resultado1 = 0;
    int resultado2 = 0;
    int resultado3 = 0;

    // Check the value ranges and assign corresponding color values
    if (val >= 0 && val < 3000) {
        resultado1 = 32736; // Color green for range 0-3000
        resultado2 = 0;
        resultado3 = 0;
    } else if (val >= 3000 && val < 6000) {
        resultado1 = 32736; // Color red for range 3000-6000
        resultado2 = 63488;
        resultado3 = 0;
    } else if (val >= 6000 && val <= 9000) {
        resultado1 = 32736; // Color blue for range 6000-9000
        resultado2 = 63488;
        resultado3 = 1055;
    }

    // Send the color values to the corresponding LEDs on the Nextion display
    NEXTION_estado_color(huart, "led1", resultado1);
    NEXTION_estado_color(huart, "led2", resultado2);
    NEXTION_estado_color(huart, "led3", resultado3);
}
