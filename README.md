# Dashboard FUEM formula student car 

Este repositorio contiene el código fuente para la interfaz de pantalla Nextion junto con el firmware para controlarla, tanto con Arduino Uno como con STM32.
![dashware_FUEM](https://github.com/guti10x/dashware_FUEM/assets/82153822/90b68f4b-f98e-4ba7-a315-11cf62342b53)

# Contenido del Repositorio:
## 1. **Interfaz Nextion:**
- **Carpeta:** `Interfaz_Nextion`
- **Descripción:** contiene el código y los recursos, incluido el archivo .HMI, para la interfaz gráfica desarrollada en Nextion Editor.
- **Interfaz:** ![interfazz_VW](https://github.com/guti10x/dashware_FUEM/assets/82153822/a8ad2718-c9cc-43a6-8d26-2878875c4afd)
- **Instrucciones para realizar cambios:**

     1. Abra el archivo .HMI en Nextion Editor.
     2. Realice los cambios necesarios.
     3. Haga clic en `File` > `TFT file output` para exportar un archivo en formato .tft.
     4. Cargue este archivo .tft en una tarjeta SD.
     5. Inserte la tarjeta SD en el lector de tarjetas de la pantalla Nextion para cargar la interfaz actualizada.

## 2. **Firmware para Arduino Uno:**

  - **Carpeta:** `Arduino/ScreenUpdater`
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

## 3. **Firmware para STM32:**
  - **Carpeta:** `stm32`
  - **Descripción:** aquí encontrarás tanto la librería como el proyecto de ejemplo desarrollado en STM32Cube IDE destinados al control de la interfaz de pantalla.
    - **Librería (nextion_comunication_lib):**
      La carpeta `stm32/nextion_comunication_lib` contiene la librería de firmware para STM32 que facilita la comunicación con la interfaz de pantalla.
    - **Proyecto STM32Cube IDE (dash_updater):**
      En la carpeta `stm32/dash_updater`, encontrarás un proyecto para STM32Cube IDE. Este proyecto, contenido en el archivo `main`, utiliza la librería mencionada anteriormente. También incluye una función de prueba que envía números aleatorios a la interfaz, mostrándolos en pantalla para comprobar su correcto funcionamiento.
- **Esquema de conexión:**
  ![stm32_conexiónV2](https://github.com/guti10x/dashware_FUEM/assets/82153822/dcfc57b8-2f26-422c-98d2-acca9b066ac5)
- **Instalación:**
  - Consulta cómo instalar e implementar la biblioteca en cualquier proyecto en STMCUBE IDE en el [manual de instalación de nextion_comunication_lib](./stm32/nextion_comunication_lib/docs/Manual%20de%20instalación%20nextion_comunication_lib.pdf).
- **Documentación:**
  - Consulta la [documentación de nextion_comunication_lib](./stm32/nextion_comunication_lib/docs/Documentación%20nextion_comunication_lib.pdf) para obtener más información sobre cómo utilizar la librería y sus características.
