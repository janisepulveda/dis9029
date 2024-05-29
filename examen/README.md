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
// configura los pines de los botones como entradas
  for (int i = 0; i <= 3; i++) {
    pinMode(botones[i], INPUT);
  }
  // inicia la semilla del generador de números aleatorios
  randomSeed(analogRead(0));
  
  // Iniciar la comunicación serie
  Serial.begin(9600);
  Serial.println("Juego de memoria iniciado.");
```

``` cpp
 // indica que el jugador ha perdido
      perder = true;
      // produce un sonido al perder
      tone(buzzer, 200);
      delay(100);
      noTone(buzzer);
      Serial.println("Secuencia incorrecta. Has perdido.");
```

## Propuestas de mejora solemne 02

- Añadir métodos de depuración en el código de Processing.

- A nivel hardware, convertir el artefacto en un objeto.

![Feedback](./assets/feedback02.png)

- servidor con una url. github pages. pasar el codigo Processing a p5.js.

## Mejoras aplicadas solemne 02

- 