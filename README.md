# Dashboard FUEM formula student car 

<p align="left">
  <img src="https://img.shields.io/badge/version-4.0-green">
  <img src="https://img.shields.io/badge/test-✓-green">
  <img src="https://img.shields.io/badge/code-C-blueviolet">
</p>

La función principal del daswhare consiste en mostrar información relevante al piloto sobre la velocidad, la marcha y las revoluciones a las que circula el coche, así como la temperatura de los frenos, la temperatura del motor, el voltaje de la batería y la aceleración y frenado del coche durante la conducción.

Además, permite mostrar alertas de forma visual y sencilla al piloto cuando es necesario detener el monoplaza debido a lecturas peligrosas de los sensores del vehículo, como una temperatura muy elevada del motor o un voltaje de la batería inadecuado.

Este repositorio contiene el código fuente para la interfaz de pantalla Nextion junto con el firmware para controlarla, tanto con Arduino Uno como con STM32.

![dashware_FUEM](https://github.com/guti10x/dashware_FUEM/assets/82153822/a761835d-2f4e-4f01-bc72-2d6ee159b520)
![renderV2](https://github.com/guti10x/dashware_FUEM/assets/82153822/01db5d63-2d34-4cf3-86f5-d116d4691659)

# Contenido del Repositorio:
## 1. **Interfaz para la pantalla Nextion (NX4827P043):**
- **Carpeta:** `Nextion - NX4827P043n`
- **Descripción:** contiene el código y los recursos, incluido el archivo .HMI, para la interfaz gráfica desarrollada en Nextion Editor.
- **Interfaz:** ![interfazz_VW](https://github.com/guti10x/dashware_FUEM/assets/82153822/a8ad2718-c9cc-43a6-8d26-2878875c4afd)
- **Instrucciones para realizar cambios:**

     1. Abra el archivo .HMI en Nextion Editor.
     2. Realice los cambios necesarios.
     3. Haga clic en `File` > `TFT file output` para exportar un archivo en formato .tft.
     4. Cargue este archivo .tft en una tarjeta SD.
     5. Inserte la tarjeta SD en el lector de tarjetas de la pantalla Nextion para cargar la interfaz actualizada.


## 2. **Firmware para la placa Nexus (STM32F103R8T6):**
  - **Carpeta:** `Nexus - stm32f103r8t6`
  - **Descripción:**
       - Aquí encontrarás el proyecto de código desarrollado para la placa STM32F103R8T6, para la comunicación, adquisición y procesado de los diferentes datos de los sensores del monoplaza. Esta unidad, conocida como NEXUS, incluirá las siguientes características: comunicación CAN-BUS, adquisición de datos en SD, control de la unidad de movimiento inercial de 6 ejes del coche, 16 pines configurables para sensores o actuadores, y comunicación UART e I2C abierta para expansiones futuras.
  - **Esquema de conexión:**
       - La pantalla Nextion se conecta mediante comunicación serial utilizando el pin Tx a la placa Nexus (stm32f103r8t6) con el objetivo de mandar y mostrar los datos de los diferentes sensores del monoplazo en la interfaz. Estos datos son obtenidos de la comunicación CAN establecida y gestionada por la placa Nexus (stm32F103R8T6) y su conexión a la centralita del coche, lugar donde todos los sensores mandan los valores leidos.

      ![stm32_conexiónV55dwdginallllllllll](https://github.com/guti10x/dashware_FUEM/assets/82153822/f326c3b8-3d8f-4221-99ca-0170c6a70b85)


  - **Contenido:**
    - **Librería nextion_comunication_lib_f1:**
      La carpeta `stm32f103r8t6/nextion_comunication_lib_f1` contiene la librería de firmware para la placa STM32F103R8T6 que facilita la comunicación con la interfaz de pantalla.
    - **Librería MPU_6050_lib:**
      La carpeta `stm32f103r8t6/MPU_6050_lib` contiene la librería para el control del sensor de movimiento inercial MPU-6050 del coche, permitiendo la lectura de datos de aceleración y giroscopio.
    - **Proyecto STM32Cube IDE (Nexus Firmware V4):**
       En la carpeta `stm32/Nexus Firmware V4`, encontrarás el proyecto para STM32Cube IDE. Este proyecto utiliza las librerías mencionadas anteriormente para recibir datos de sensores a través de CAN-BUS, procesarlos, mostrarlos en la interfaz, y almacenarlos en una tarjeta SD.


## 3. **Firmware para la placa NucleoF4 (nucleo-f411re):**
  - **Carpeta:** `NucleoF4 - nucleo-f411re`
  - **Descripción:**
       - aquí encontrarás tanto la librería como el proyecto de ejemplo desarrollado en STM32Cube IDE destinados al control de la interfaz de pantalla.
  - **Contenido:**
    - **Librería (nextion_comunication_lib_f4):**
      La carpeta `stm32/nextion_comunication_lib_f4` contiene la librería de firmware para STM32f4 que facilita la comunicación con la interfaz de pantalla.
    - **Proyecto STM32Cube IDE (dash_updater):**
      En la carpeta `stm32/dash_updater`, encontrarás un proyecto para STM32Cube IDE. Este proyecto, contenido en el archivo `main`, utiliza la librería mencionada anteriormente. También incluye una función de prueba que envía números aleatorios a la interfaz, mostrándolos en pantalla para comprobar su correcto funcionamiento.
- **Esquema de conexión:**
  ![stm32_conexiónV2](https://github.com/guti10x/dashware_FUEM/assets/82153822/dcfc57b8-2f26-422c-98d2-acca9b066ac5)
- **Instalación:**
  - Consulta cómo instalar e implementar la biblioteca en cualquier proyecto en STMCUBE IDE en el [manual de instalación de nextion_comunication_lib](NucleoF4%20-%20nucleo-f411re/nextion_comunication_lib_f4/docs/Manual%20de%20instalación%20nextion_comunication_lib.pdf).
- **Documentación:**
  - Consulta la [documentación de nextion_comunication_lib](./NucleoF4%20-%20nucleo-f411re/nextion_comunication_lib_f4/docs/Documentación%20nextion_comunication_lib.pdf) para obtener más información sobre cómo utilizar la librería y sus características.

## 4. **Firmware para la placa Arduino Uno:**

  - **Carpeta:** `Arduino - Arduino UNO`
  - **Descripción:** contiene el código fuente para el firmware que controla la interfaz de pantalla en un Arduino Uno.
  - **Esquema de conexión:**
    ![arduino_conexiónV2](https://github.com/guti10x/dashware_FUEM/assets/82153822/2aa48b07-787d-4e32-90cc-13cbd44ab1e0)
  - **IDE de desarrollo:**
    - Se recomienda el uso del entorno de desarrollo integrado Arduino IDE para cargar y modificar el firmware en la placa Arduino Uno.
  - **Librerías necesarias:** asegúrese de tener las siguientes librerías instaladas para compilar y cargar el firmware en la placa Arduino Uno:
    - `Arduino.h`
    - `SoftwareSerial.h`
    - `Nextion.h`
  - **Instrucciones de instalación de librerías:** para instalar estas librerías, siga estos pasos:

     1. Abra Arduino IDE.
     2. Vaya a `Sketch` > `Incluir Biblioteca` > `Gestionar Bibliotecas...`.
     3. En el cuadro de búsqueda, escriba el nombre de la librería que necesita instalar.
     4. Haga clic en la librería en los resultados de la búsqueda.
     5. Haga clic en el botón `Instalar`.