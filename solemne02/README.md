# Solemne 02

## Fechas importantes

- 17/04 Wearable Computing 1
- 24/04 Wearable Computing 2
- 01/05 Feriado
- 08/05 Taller de producción - presentación solemne 02
- 15/05 Taller de producción

## Descripción del artefacto (proceso)

- Collar interactivo de pulso utilizando Arduino. El dispositivo está diseñado para medir el ritmo cardíaco del usuario a través de un sensor integrado en el collar y mostrar visualmente el pulso en una pantalla OLED.

- El proyecto consta de dos funcionalidades principales:

  - **Sensor y Arduino del Collar:** Este componente mide el pulso del usuario y envía los datos a un Arduino emparejado a través de una conexión inalámbrica. Para esto se desarrollaron 2 prototipos de códigos:
```cpp
    // Definicion del pin conectado al sensor de pulso
const int pinSensorPulso = A5; 

int frecCardiacaMin = 60;
int frecCardiacaMax = 100;

void setup() {
  // Iniciar comunicacion serial para mostrar datos
  Serial.begin(9600);   

  // Configurar el pin del sensor como entrada 
  pinMode(pinSensorPulso, INPUT);
}

void loop() {
  // Leer valor del sensor de pulso
  int valorSensor = analogRead(pinSensorPulso);

  if (valorSensor >= frecCardiacaMin && valorSensor <= frecCardiacaMax) {
    Serial.print("Frecuencia cardiaca: ");
    Serial.println(valorSensor);

  } else {
    // Si está fuera del rango, imprimir mensaje "fuera de rango"
    Serial.println("Frecuencia cardiaca fuera de rango");
  }

  // Esperar un segundo antes de la siguiente lectura
  delay(1000);
}
```   
  - Este código no sirvió porque tiene valores mínimos y máximos para la frecuencia cardiaca leída en segundos, el sensor lee el general de las pulsaciones, los valores suben infinitamente. Solo funcionaría si la frecuencia es leída en latidos por minuto. Por lo tanto simplifiqué el código:

```cpp
int pulso = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A2, INPUT);
}

void loop() {
  pulso = analogRead(A2);
  delay(1000);
  Serial.println(pulso);
}
```
  - A pesar de que es un código muy simple funciona bien para lo que necesito, decidí quedarme con este.

    - **Arduino y Pantalla:** El segundo Arduino recibe la señal del pulso y la interpreta para mostrar una animación en una pantalla OLED, reflejando el ritmo cardíaco del usuario de manera visual. El código de la animación fue desarrollado en Processing y será conectado a través de la comunicación serial.
   
```java
// variable para almacenar el tiempo transcurrido
float tiempo;

// color base 1 (rojo)
color colorPrincipal1 = color(255, 0, 0);

// color base 2 (azul)
color colorPrincipal2 = color(100, 0, 255);

// numero de elipses a dibujar
int numeroElipses = 70;

void setup() {
  // establecer el tamano de la ventana segun la resolucion de la pantalla oled
  size(1080, 700);
  // eliminar el trazo
  noStroke();
}

void draw() {
  // borrar el fondo
  background(0);

  // actualizar el tiempo para la animacion
  tiempo += 0.05; 

  // obtener el ancho y el alto de la ventana
  float anchoVentana = width;
  float altoVentana = height;

  // calcular el valor del pulso base en funcion del tiempo y la funcion seno
  float pulso = sin(tiempo) * min(anchoVentana, altoVentana) / 1.5;

  // bucle para dibujar multiples elipses
  for (int i = 0; i < numeroElipses; i++) {
    // calcular el desplazamiento individual del pulso y el cambio de color
    float desplazamiento = sin(tiempo + i * 0.1) * pulso;
    // ajustar el cambio de color segun el indice del bucle
    float cambioColor = abs(sin(tiempo + i * 0.2)); 

    // calcular la posicion de la elipse en funcion del tamano de la ventana y el pulso
    float centroX = map(i, 0, numeroElipses - 1, anchoVentana / 2, 4 * anchoVentana / 2);

    // posicionar las elipses verticalmente con un espaciado uniforme
    float centroY = altoVentana / 2 - i * 30;

    // crear una elipse con tamano y cambio de color pulsantes
    fill(lerpColor(colorPrincipal1, colorPrincipal2, cambioColor), pulso + desplazamiento);
    ellipse(centroX, centroY, pulso + desplazamiento, pulso + desplazamiento);
  }
}
```
  - Este código muestra la animación que quiero lograr. La idea es que sea reactiva a las pulsaciones enviadas por arduino.

![Animación](./animacionProcessing.gif)

- Como referente para contener los elementos del hardware estoy usando las obras de Peter Vogel:

![Peter Vogel](./peterVogel.png)

## Descripción del artefacto 

El proyecto consiste en un sistema de comunicación basado en WiFi entre dos microcontroladores Arduino, un servidor y un cliente, y Processing. Arduino actúa como un dispositivo de adquisición de datos del sensor, mientras que la aplicación Processing sirve como una herramienta de visualización de datos.

## Tecnologías y Herramientas de trabajo

- 2x Arduino UNO R4 wifi.
- Cables.
- Alambre.
- Pilas.
- Sensor de pulso cardiaco.

## Instrucciones de instalación

1. Asignar roles a cada arduino:

  - El Arduino designado como servidor tendrá conectado el sensor de pulso cardiaco.
  - El Arduino designado como cliente estará conectado al computador y se conectará via comunicación serial a Processing.

2. Configuración del hardware:

  - Conectar el sensor al pin análogo 0 del Arduino escogido como servidor.
  - Asegurar una fuente de alimentación adecuada para el Arduino y el sensor.
  
3. Desarrollo del código Arduino:

  - Subir los códigos Arduino proporcionados en el repositorio de GitHub a los microcontroladores Arduino.
  - Estos códigos configuran la conexión WiFi, lee datos del sensor y los envía a la aplicación Processing.
  
4. Desarrollo del código Processing:

  - Subir el código a Processing proporcionado en el repositorio de GitHub.
  - Este código establece la comunicación serial, recibe datos del sensor del Arduino, los procesa y los transforma en una animación visual.

## Bibliografía

https://github.com/arduino-libraries/ArduinoHttpClient/blob/master/examples/SimpleGet/SimpleGet.ino
https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/#wi-fi-web-client
https://docs.arduino.cc/tutorials/uno-r4-wifi/wifi-examples/#wi-fi-web-server
  


