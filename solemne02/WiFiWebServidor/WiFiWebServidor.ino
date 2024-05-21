// Tecnologías Interactivas - solemne 02
// q hace este codigo?
// Código para crear el servidor
// Código referenciado de los ejemplos de la librería
// "WiFiS3". Se modificaron partes del código original
// Para adaptarlas a las necesidades de la entrega.

// Incluir biblioteca WiFi para la comunicación de red
#include "WiFiS3.h"
// Incluir archivo para credenciales sensibles
#include "arduino_secrets.h"

// Datos confidenciales
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;

// Variable para almacenar el estado de la conexión WiFi
int status = WL_IDLE_STATUS;

// Pin del sensor de pulso
const int pinSensorPulso = A0;

// Crear un servidor WiFi en el puerto 80
WiFiServer server(80);

void setup() {
  // Initialize serial and sensor pin
  Serial.begin(9600);
  // Configurar el pin del sensor de pulso
  pinMode(pinSensorPulso, INPUT);

  // Esperar a que se abra el puerto serie para evitar errores
  while (!Serial) {
    ; 
  }

  // Verificar si ya hay conexión WiFi establecida
  if (WiFi.status() != WL_CONNECTED) {
    // Si no hay conexión, intentar conectarse a la red WiFi especificada
    while (status != WL_CONNECTED) {
      Serial.print("Conectando a la red WiFi: ");
      Serial.println(ssid);
      status = WiFi.begin(ssid, pass);
      delay(1000);
    }
  }

  // Iniciar el servidor WiFi en el puerto 80
  server.begin();

  // Imprimir información sobre la conexión WiFi
  printWifiStatus();
}

void loop() {
  // Leer valor del sensor
  int valorSensor = analogRead(pinSensorPulso); 

  // Filtrar la data del sensor
  if (valorSensor > 104) {
    // Enviar la data del sensor al cliente
    WiFiClient client = server.available();
    if (client) {
      Serial.println("Nuevo cliente conectado");
      // Enviar el valor filtrado al cliente como una string
      client.println(String(valorSensor));
      delay(1); 
      
      // Mantener la conexión abierta
      Serial.println("Cliente todavía conectado");
    }
  }

  delay(1000); 
}

void printWifiStatus() {

  // Imprimir SSID de la red WiFi conectada
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Dirección IP: ");
  // Imprimir la dirección IP de la placa Arduino
  Serial.println(WiFi.localIP());
  // Imprimir la intensidad de la señal recibida
  Serial.print("Fuerza de la señal (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

