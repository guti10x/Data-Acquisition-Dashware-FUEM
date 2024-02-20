#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Nextion.h"

// Configuración de pines para la comunicación serial
SoftwareSerial nextion(2, 3); // RX, TX

// Elementos de la pantalla Nextion
NexText gear = NexText(0, 1, "t6"); //Gear
NexText speedd = NexText(0, 1, "Speed"); //Speed
NexText rpm = NexText(0, 19, "t10");  //RPM
NexText engineTemp = NexText(0, 3, "engineTemp"); //Engine Temp
NexText voltage = NexText(0, 8, "Voltage"); //Battery Vol

//Pedals
NexProgressBar acePedal = NexProgressBar(0, 5, "acePedal"); //Ace pedal
NexProgressBar brakePedal = NexProgressBar(0, 4, "brakePedal"); //Brake pedal

//indicadores revoluciones
NexText texts[] = {
    NexText(0, 36, "t24"),
    NexText(0, 37, "t25"),
    NexText(0, 28, "t14"),
    NexText(0, 29, "t15"),
    NexText(0, 30, "t16"),
    NexText(0, 31, "t17"),
    NexText(0, 32, "t18"),
    NexText(0, 33, "t19"),
    NexText(0, 34, "t22"),
    NexText(0, 35, "t23"),
    NexText(0, 26, "t12"),
    NexText(0, 27, "t13"),
    NexText(0, 25, "t21"),
    NexText(0, 24, "t22"),
    NexText(0, 23, "t29")
};

//Estados indicadores de rpms
int colors[15][15] = {{2016, 1024, 1024, 1024, 1024, 147, 147, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 1024, 1024, 1024, 147, 147, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 1024, 1024, 147, 147, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 1024, 147, 147, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 147, 147, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 147, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 147, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 147, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 147, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 10623, 38912, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 10623, 63781, 38912, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 10623, 63781, 63781, 38912, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 10623, 63781, 63781, 63781, 38912, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 10623, 63781, 63781, 63781, 63781, 38912},
                      {2016, 2016, 2016, 2016, 2016, 10623, 10623, 10623, 10623, 10623, 63781, 63781, 63781, 63781, 63781}};

void setup() {
  nextion.begin(9600);
  nexInit();
}
int vel=0;

void loop() {

  //Pedals movement
  acePedal.setValue(vel);
  brakePedal.setValue(vel);
  
  String textoConvertido = String(vel);
  const char* textoChar = textoConvertido.c_str();
  speedd.setText(textoChar);
  engineTemp.setText(textoChar);
  voltage.setText(textoChar);
  
  //Calculamos el num de cuadrados de rpms
  int numTexts = vel / sizeof(texts[0]);    //59/10=5
  String textoCo = String(numTexts);
  const char* textoCh = textoCo.c_str();
  rpm.setText(textoCh);
  gear.setText(textoCh);
  
  int pos=0;
  for (int i = 0; i < numTexts; ++i) {
    texts[i].Set_background_color_bco(colors[i][pos]);
    pos++;
 }
 vel++;
}
