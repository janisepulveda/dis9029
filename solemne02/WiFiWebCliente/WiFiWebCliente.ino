// Tecnologías Interactivas - solemne 02
// q hace este codigo?
// Código para crear el cliente
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

// Seguimiento del estado de conexión WiFi
int status = WL_IDLE_STATUS;

// Dirección IP del servidor
IPAddress server(172, 20, 10, 10); 

// Crear un cliente WiFi para la comunicación
WiFiClient client;

void setup() {
  Serial.begin(9600);
  // Esperar a que se abra el puerto serie
  while (!Serial) { ; } 

  // Verificar la presencia del módulo WiFi y la versión del firmware
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Falló la comunicación con el módulo WiFi");
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade WiFi firmware");
  }

  // Intentar conectarse a la red WiFi
  while (status != WL_CONNECTED) {
    Serial.print("Conectando a SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000); 
  }

  // Imprimir información de conexión WiFi
  printWifiStatus();

  Serial.println("Conectando al servidor...");
  if (client.connect(server, 80)) {
    Serial.println("Conectado al servidor");
  }
}

void loop() {
  // Enviar solicitud HTTP GET para datos del sensor
  client.println("GET /sensor_data HTTP/1.1");
  client.println("Se cerró la conexión");
  client.println();

  // Leer y mostrar los datos de respuesta del servidor
  read_response();

  // Verificar si la conexión al servidor sigue activa
  if (!client.connected()) {
    Serial.println("Desconectado del servidor");
    client.stop();
    while (true);
  }

  delay(1000);
}

void read_response() {
  // Contar bytes de datos recibidos
  uint32_t received_data_num = 0;
  while (client.available()) {
    // Leer un solo carácter
    char c = client.read();
    // Imprimir el carácter recibido en el monitor serial
    Serial.print(c);
    // Incrementar el contador de bytes de datos
    received_data_num++;
    
    // Ajustar los datos a 80 columnas para facilitar su lectura
    if (received_data_num % 80 == 0) {
      Serial.println();
    }
  }
}

void printWifiStatus() {
  
  // Imprimir SSID de la red WiFi conectada
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Dirección IP: ");
  // Imprimir la dirección IP de la placa Arduino
  Serial.println(WiFi.localIP());
  // Imprimir la intensidad de la señal recibida
  Serial.print("Intensidad de la señal (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

