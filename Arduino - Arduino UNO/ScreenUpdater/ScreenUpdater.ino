#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Nextion.h"

// Configuración de pines para la comunicación serial
SoftwareSerial nextion(2, 3); // RX, TX

//Parameters
NexText gear = NexText(0, 17, "gear"); //Gear
NexText speedd = NexText(0, 1, "Speed"); //Speed
NexText rpm = NexText(0, 19, "rpm");  //RPM
NexText engineTemp = NexText(0, 3, "engineTemp"); //Engine Temp
NexText voltage = NexText(0, 2, "Voltage"); //Battery Vol

//Pedals
NexProgressBar acePedal = NexProgressBar(0, 5, "acePedal"); //Ace pedal
NexProgressBar brakePedal = NexProgressBar(0, 4, "breakPedal"); //Brake pedal

//Breaks
NexText breaks[] = {
    NexText(0, 6, "brake1"), // Break 1
    NexText(0, 9, "brake2"), // Break 2
    NexText(0, 7, "brake3"), // Break 3
    NexText(0, 8, "brake4")  // Break 4
};

//Indicadores revoluciones
NexProgressBar rpmindex1 = NexProgressBar(0, 27, "rpmsi1");
NexProgressBar rpmindex2 = NexProgressBar(0, 28, "rpmsi2");
NexProgressBar rpmindex3 = NexProgressBar(0, 29, "rpmsi3");

void setup() {
  nextion.begin(9600);
  nexInit();
}
int vel=0;

void loop() {

  //Pedals movement
  acePedal.setValue(vel);
  brakePedal.setValue(vel);

  //Velocidad
  String textoConvertido = String(vel);
  const char* textoChar = textoConvertido.c_str();
  speedd.setText(textoChar);

  //Temperatura motor
  engineTemp.setText(textoChar);
  if(vel>150){
    engineTemp.Set_background_color_bco(63488); // Red
    rpm.Set_background_color_bco(63488); // Red 
    gear.Set_background_color_bco(63488); // Red
    speedd.Set_background_color_bco(63488); // Red 
  }

  //Voltaje bateria
  voltage.setText(textoChar);
  if(vel>150){
    voltage.Set_background_color_bco(63488); // Red
    rpm.Set_background_color_bco(63488); // Red 
    gear.Set_background_color_bco(63488); // Red
    speedd.Set_background_color_bco(63488); // Red 
  }

  //Breaks
  for (int i = 0; i < 4; ++i) {
    breaks[i].setText(textoChar);
    if (vel >= 80) {
      breaks[i].Set_background_color_bco(63488); // Rojo 
      
    } else if (vel >= 60 && vel <= 80) {
      breaks[i].Set_background_color_bco(62757); // Naranja  
    } else {
      breaks[i].Set_background_color_bco(36609); // Verde -> OK
    }
  }
  
  //RPM value
  int numTexts = vel / 15; 
  String textoCo = String(numTexts);
  const char* textoCh = textoCo.c_str();
  rpm.setText(textoCh);
  gear.setText(textoCh);

  //RPMs indicator
  
  if (vel >= 72) {
    rpmindex1.setValue(100);
    rpmindex2.setValue(100);
    rpmindex3.setValue(vel);
  } else if (vel >= 36 && vel <= 72) {
    rpmindex1.setValue(100);
    rpmindex2.setValue(vel);
    rpmindex3.setValue(0);    
  } else {
    rpmindex1.setValue(vel);
    rpmindex2.setValue(0);
    rpmindex3.setValue(0);
  }
  
  vel++;
}
