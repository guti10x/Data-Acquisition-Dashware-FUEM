#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Nextion.h"

// Configuración de pines para la comunicación serial
SoftwareSerial nextion(2, 3); // RX, TX

// Elemento de pantalla Nextion
NexText t6 = NexText(0, 1, "t6");

void setup() {
  // Inicialización de la comunicación serial y Nextion
  nextion.begin(9600);
  nexInit();
}

void loop() {
  // Actualizar el texto del elemento de pantalla a "1"
  t6.setText("1");

  // Esperar un breve período de tiempo
  delay(1500);

  // Actualizar el texto del elemento de pantalla a "2"
  t6.setText("2");

  // Esperar nuevamente antes de repetir
  delay(1500);
}
