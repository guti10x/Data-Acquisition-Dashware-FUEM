#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Nextion.h"

// Configuración de pines para la comunicación serial
SoftwareSerial nextion(2, 3); // RX, TX

// Elementos de la pantalla Nextion
//Gear
NexText t6 = NexText(0, 1, "t6");
//Speed
NexText speedd = NexText(0, 1, "Speed");
//RPM
NexText rpm = NexText(0, 19, "t10");

NexText t24 = NexText(0, 36, "t24");
NexText t25 = NexText(0, 37, "t25");
NexText t14 = NexText(0, 28, "t14");
NexText t15 = NexText(0, 29, "t15");
NexText t16 = NexText(0, 30, "t16");
NexText t17 = NexText(0, 31, "t17");
NexText t18 = NexText(0, 32, "t18");
NexText t19 = NexText(0, 33, "t19");
NexText t22 = NexText(0, 34, "t22");
NexText t23 = NexText(0, 35, "t23");
NexText t12 = NexText(0, 26, "t12");
NexText t13 = NexText(0, 27, "t13");
NexText t21 = NexText(0, 25, "t21");
NexText t20 = NexText(0, 24, "t22");
NexText t29 = NexText(0, 23, "t29");

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
  int vel = 0;

  for (int i = 0; i < 100; i++) {
    String textoConvertido = String(vel);
    const char* textoChar = textoConvertido.c_str();

    // Actualizar solo los elementos que han cambiado
    speedd.setText(textoChar);
    rpm.setText(textoChar);
    t6.setText(textoChar);
    brake1.setText(textoChar);
    brake2.setText(textoChar);
    brake3.setText(textoChar);
    brake4.setText(textoChar);
    engineTemp.setText(textoChar);
    voltage.setText(textoChar);
    acePedal.setValue(textoChar);
    brakePedal.setValue(textoChar);

    // Actualizar otros elementos si es necesario...

    delay(1);  // Omitir o ajustar según la necesidad

    vel++;
  }
}
