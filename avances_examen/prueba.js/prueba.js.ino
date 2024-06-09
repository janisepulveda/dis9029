/*
 * Creado por ArduinoGetStarted.com
 *
 * Este código de ejemplo es de dominio público
 *
 * Página del tutorial: https://arduinogetstarted.com/tutorials/arduino-web-server
 */

#include <WiFiS3.h>

// cambia el nombre de tu red
const char ssid[] = "Janis";  
// cambia la contraseña de tu red (utiliza WPA/WPA2)
const char pass[] = "madsmikkelsen";   

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  // iniciar serial y esperar a que el puerto se abra:
  Serial.begin(9600);

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION)
    Serial.println("Por favor, actualiza el firmware");

  // intentar conectarse a la red WiFi:
  while (status != WL_CONNECTED) {
    Serial.print("Intentando conectarse a SSID: ");
    Serial.println(ssid);
    // conectarse a la red WPA/WPA2. Cambia esta línea si usas una red abierta o WEP:
    status = WiFi.begin(ssid, pass);

    // esperar 10 segundos para la conexión:
    delay(10000);
  }
  server.begin();
  // ya estás conectado, así que imprime el estado:
  printWifiStatus();
}

void loop() {
  // escuchar clientes entrantes
  WiFiClient client = server.available();
  if (client) {
    // leer la cabecera de la solicitud HTTP línea por línea
    while (client.connected()) {
      if (client.available()) {
        // leer la línea de la cabecera de la solicitud HTTP
        String HTTP_header = client.readStringUntil('\n');  

        // el fin de la solicitud HTTP
        if (HTTP_header.equals("\r"))  
          break;

        Serial.print("<< ");
        // imprimir solicitud HTTP en el Monitor Serial
        Serial.println(HTTP_header);  
      }
    }

    // enviar la respuesta HTTP
    // enviar la cabecera de la respuesta HTTP
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    // la conexión se cerrará después de completar la respuesta
    client.println("Connection: close");  
    // el separador entre la cabecera HTTP y el cuerpo
    client.println();                     
    // enviar el cuerpo de la respuesta HTTP
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    client.println("<style>");
    client.println("  #ball {");
    client.println("    width: 50px;");
    client.println("    height: 50px;");
    client.println("    background-color: red;");
    client.println("    border-radius: 50%;");
    client.println("    position: absolute;");
    client.println("    top: 50%;");
    client.println("    left: 0;");
    client.println("  }");
    client.println("</style>");
    client.println("<script>");
    client.println("  let pos = 0;");
    client.println("  let direction = 1;");
    client.println("  function animate() {");
    client.println("    pos += direction;");
    client.println("    if (pos > window.innerWidth - 50 || pos < 0) {");
    client.println("      direction *= -1;");
    client.println("    }");
    client.println("    document.getElementById('ball').style.left = pos + 'px';");
    client.println("    requestAnimationFrame(animate);");
    client.println("  }");
    client.println("  window.onload = function() {");
    client.println("    animate();");
    client.println("  };");
    client.println("</script>");
    client.println("</head>");
    client.println("<body>");
    client.println("<div id='ball'></div>");
    client.println("</body>");
    client.println("</html>");
    client.flush();

    // dar tiempo al navegador web para recibir los datos
    delay(10);

    // cerrar la conexión:
    client.stop();
  }
}

void printWifiStatus() {
  // imprimir la dirección IP de tu placa:
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // imprimir la intensidad de la señal recibida:
  Serial.print("Intensidad de la señal (RSSI):");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}
