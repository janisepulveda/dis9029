# Examen

## Fechas importantes

- 29/05 Taller de producción.

## Propuestas de mejora solemne01

- Añadir métodos de depuración al nivel código.

![Feedback](./assets/feedback.png)

- A nivel hardware, añadir un case que contenga el circuito.

- sacar el protoboard. conectar todo directo a Arduino

## Mejoras aplicadas solemne 01

- A nivel software:

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

``` cpp
 void iniciarJuego() {
  ronda = 0;
  paso = 0;
  perder = false;
  secuencia[ronda] = random(0, 3);
  ronda++;
 }
```

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

- A nivel de hardware:
  - Sacar el protoboard y soldar cables para que todo quede unido al Arduino.

## Propuestas de mejora solemne 02

- Añadir métodos de depuración en el código de Processing.

- A nivel hardware, convertir el artefacto en un objeto.

![Feedback](./assets/feedback02.png)

- servidor con una url. github pages. pasar el codigo Processing a p5.js.

## Mejoras aplicadas solemne 02
