# Examen

## Fechas importantes

- 29/05 Taller de producción.

## Propuestas de mejora solemne01

- Añadir métodos de depuración al nivel código.

![Feedback](./assets/feedback.png)

- A nivel hardware, añadir un case que contenga el circuito.

- Sacar el protoboard. conectar todo directo a Arduino

## Mejoras aplicadas solemne 01

A nivel software:

- Botón encendido/apagado:

```cpp
// según el estado del botón, imprime en la consola encendido o apagado
  estadoBoton = digitalRead(pinBoton);
  if (estadoBoton != ultimoEstadoBoton) {
    if (estadoBoton == HIGH) {
      juegoEncendido = !juegoEncendido;
      if (juegoEncendido) {
        Serial.println("Juego de memoria encendido.");
        iniciarJuego();
      } else {
        Serial.println("Juego de memoria apagado.");
        apagarJuego();
      }
    }
    ultimoEstadoBoton = estadoBoton;
  }

  if (juegoEncendido && !perder) {
    jugarRonda();
  }
```

- Función para iniciar el juego:

``` cpp
 void iniciarJuego() {
  ronda = 0;
  paso = 0;
  perder = false;
  secuencia[ronda] = random(0, 3);
  ronda++;
 }
```

- Función para apagar el juego:

```cpp
void apagarJuego() {
  // apaga los LEDs y el buzzer
  noTone(buzzer);
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }
  // reinicia el juego
  ronda = 0;
  perder = false;
}
```

A nivel de hardware:

- Sacar el protoboard y soldar cables para que todo quede unido al Arduino.

## Propuestas de mejora solemne 02

- Añadir métodos de depuración en el código de Processing.

- A nivel hardware, convertir el artefacto en un objeto.

![Feedback](./assets/feedback02.png)

- servidor con una url. github pages. pasar el codigo Processing a p5.js.

## Mejoras aplicadas solemne 02

A nivel software:

- Investigación, escritura y modificación de un código de prueba para crear un servidor web a través de Arduino que sea capaz de mostrar una animación JavaScript simple:

```cpp
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
```

Vista previa del código en la web:

![Vista previa del código en la web](./assets/serverJS.gif)
