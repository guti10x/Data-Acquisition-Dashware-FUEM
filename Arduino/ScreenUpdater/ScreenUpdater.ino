#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Nextion.h"

// Configuración de pines para la comunicación serial
SoftwareSerial nextion(2, 3); // RX, TX

// Elementos de la pantalla Nextion
//Gear
NexText t6 = NexText(0, 1, "t6");
//Speed
NexText Speed = NexText(0, 1, "Speed");
//RPM
NexText Rpm = NexText(0, 19, "t10");

//Breaks
//Break 1
NexText brake1 = NexText(0, 6, "brake1");
//Break 2
NexText brake2 = NexText(0, 9, "brake2");
//Break 3
NexText brake3 = NexText(0, 7, "brake3");
//Break 4
NexText brake4 = NexText(0, 8, "brake4");

//Engine Temp
NexText engineTemp = NexText(0, 3, "engineTemp");
//Battery Vol
NexText voltage = NexText(0, 8, "Voltage");

//Pedales
//Ace pedal
NexProgressBar acePedal = NexProgressBar(0, 5, "acePedal");
//Brake pedal
NexProgressBar brakePedal = NexProgressBar(0, 4, "brakePedal");


void setup() {
  // Inicialización de la comunicación serial y Nextion
  nextion.begin(9600);
  nexInit();
}

void loop() {
  
  t6.setText("1");

  Speed.setText("1");
  Rpm.setText("1");
  
  brake1.setText("1");
  brake2.setText("1");
  brake3.setText("1");
  brake4.setText("1");

  engineTemp.setText("1");
  voltage.setText("1");

  acePedal.setValue(10);
  brakePedal.setValue(10);

  delay(1500);

  t6.setText("2");

  Speed.setText("2");
  Rpm.setText("2");
  
  brake1.setText("2");
  brake2.setText("2");
  brake3.setText("2");
  brake4.setText("2");

  delay(1500);
}
