#include <WiFiS3.h>
#include "arduino_secrets.h"

// Datos confidenciales
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

const int pulsePin = A0;  // Pin analógico al que está conectado el sensor de pulso
int pulseValue = 0;  // Valor leído del sensor de pulso

void setup() {
  // Iniciar serial y esperar a que el puerto se abra:
  Serial.begin(9600);

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    Serial.println("Por favor, actualiza el firmware");

  // Intentar conectarse a la red WiFi:
  while (status != WL_CONNECTED) {
    Serial.print("Intentando conectarse a SSID: ");
    Serial.println(ssid);
    // Conectarse a la red WPA/WPA2. Cambia esta línea si usas una red abierta o WEP:
    status = WiFi.begin(ssid, pass);

    // Esperar 10 segundos para la conexión:
    delay(10000);
  }
  server.begin();
  // Ya estás conectado, así que imprime el estado:
  printWifiStatus();
}

void loop() {
  // Leer el valor del sensor de pulso
  pulseValue = analogRead(pulsePin);

  // Escuchar clientes entrantes
  WiFiClient client = server.available();
  if (client) {
    // Leer la cabecera de la solicitud HTTP línea por línea
    while (client.connected()) {
      if (client.available()) {
        // Leer la línea de la cabecera de la solicitud HTTP
        String HTTP_header = client.readStringUntil('\n');  

        // El fin de la solicitud HTTP
        if (HTTP_header.equals("\r"))  
          break;

        Serial.print("<< ");
        // Imprimir solicitud HTTP en el Monitor Serial
        Serial.println(HTTP_header);  
      }
    }

    // Enviar la respuesta HTTP
    // Enviar la cabecera de la respuesta HTTP
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    // La conexión se cerrará después de completar la respuesta
    client.println("Connection: close");  
    // El separador entre la cabecera HTTP y el cuerpo
    client.println();                     
    // Enviar el cuerpo de la respuesta HTTP
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/p5.js/1.4.0/p5.js\"></script>");
    client.println("<script>");
    client.println("let tiempo = 0;");
    client.println("let colorPrincipal1;");
    client.println("let colorPrincipal2;");
    client.println("let numeroElipses = 70;");
    client.println("let pulsoSensor = " + String(pulseValue) + ";");  // Enviar valor del sensor al cliente
    client.println("function setup() {");
    client.println("  createCanvas(windowWidth, windowHeight);");
    client.println("  colorPrincipal1 = color(255, 0, 0);");
    client.println("  colorPrincipal2 = color(100, 0, 255);");
    client.println("  noStroke();");
    client.println("}");
    client.println("function draw() {");
    client.println("  background(0);");
    client.println("  tiempo += 0.05;");
    client.println("  let anchoVentana = width;");
    client.println("  let altoVentana = height;");
    client.println("  let pulso = sin(tiempo) * min(anchoVentana, altoVentana) / 1.5;");
    client.println("  for (let i = 0; i < numeroElipses; i++) {");
    client.println("    let desplazamiento = sin(tiempo + i * 0.1) * pulso;");
    client.println("    let cambioColor = abs(sin(tiempo + i * 0.2));");
    client.println("    let centroX = map(i, 0, numeroElipses - 1, anchoVentana / 2, 4 * anchoVentana / 2);");
    client.println("    let centroY = altoVentana / 2 - i * 30;");
    client.println("    fill(lerpColor(colorPrincipal1, colorPrincipal2, cambioColor));");
    client.println("    ellipse(centroX, centroY, pulso + desplazamiento, pulso + desplazamiento);");
    client.println("  }");
    client.println("}");
    client.println("</script>");
    client.println("</head>");
    client.println("<body>");
    client.println("</body>");
    client.println("</html>");
    client.flush();

    // Dar tiempo al navegador web para recibir los datos
    delay(10);

    // Cerrar la conexión:
    client.stop();
  }
}

void printWifiStatus() {
  // Imprimir la dirección IP de tu placa:
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Imprimir la intensidad de la señal recibida:
  Serial.print("Intensidad de la señal (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
