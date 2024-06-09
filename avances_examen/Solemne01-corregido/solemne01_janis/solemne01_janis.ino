/*
  Juego de memoria.
  Código escrito por Janis Sepúlveda.
  10-04-2024
  Juego de memoria interactivo en el que el jugador deberá memorizar 
  una secuencia de luces LEDs y sonidos, y reproducirlos mediante pulsadores.
*/

// arreglo para almacenar la secuencia de luces que se mostrarán al jugador
int secuencia[100];
// variable para realizar un seguimiento de la ronda actual del juego
int ronda = 0;
// variable para realizar un seguimiento del paso actual dentro de una ronda
int paso = 0;
// LEDs verde, amarillo, azul
int leds[3] = { 3, 4, 5 };
// botones verde, amarillo, azul, pines análogos
int botones[3] = { A3, A4, A5 }; 
// variable que almacena el índice del botón que el jugador ha presionado
int botonPresionado = 0;
// variable que indica si el jugador ha perdido el juego
bool perder = false;
// pin al que está conectado el buzzer
int buzzer = 6;
// arreglo que contiene los tonos correspondientes a los LEDs
int sonidos[3] = { 400, 450, 500 };
// pin del botón (analógico A2)
const int pinBoton = A2; 
// variable para almacenar el estado del botón
int estadoBoton = 0;   
// variable para almacenar el último estado del botón   
int ultimoEstadoBoton = LOW; 
// variable que indica si el juego está encendido o no
bool juegoEncendido = false;

void setup() {
  pinMode(pinBoton, INPUT);
  // iniciar la comunicación serie
  Serial.begin(9600);

  // configura el pin del buzzer como salida
  pinMode(buzzer, OUTPUT);
  // configura los pines de los LEDs como salidas
  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
  // configura los pines de los botones como entradas
  for (int i = 0; i < 3; i++) {
    pinMode(botones[i], INPUT);
  }
  // inicia la semilla del generador de números aleatorios
  randomSeed(analogRead(0));
}

void loop() {
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
}

void iniciarJuego() {
  ronda = 0;
  paso = 0;
  perder = false;
  secuencia[ronda] = random(0, 3);
  ronda++;

  // melodía al iniciar el juego
  tone(buzzer, 500);
  delay(200);
  tone(buzzer, 600);
  delay(200);
  tone(buzzer, 700);
  delay(200);
  noTone(buzzer);

  // encendido de los LEDs al iniciar el juego
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }
}

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

void jugarRonda() {
  // muestra la secuencia de luces al jugador
  for (int i = 0; i < ronda; i++) {
    digitalWrite(leds[secuencia[i]], HIGH);
    tone(buzzer, sonidos[secuencia[i]]);
    delay(500); 
    digitalWrite(leds[secuencia[i]], LOW);
    noTone(buzzer);
    delay(100); 
  }

  // el jugador repite la secuencia mostrada
  for (int i = 0; i < ronda; i++) {
    boolean jugadaEfectuada = false;
    while (!jugadaEfectuada) {
      for (int j = 0; j < 3; j++) {
        if (analogRead(botones[j]) > 900) {
          botonPresionado = j;
          digitalWrite(leds[j], HIGH);
          // enciende el buzzer con la misma frecuencia que el LED
          tone(buzzer, sonidos[j]);
          delay(300); 
          digitalWrite(leds[j], LOW);
          // detiene el tono del buzzer
          noTone(buzzer);
          jugadaEfectuada = true;
        }
      }
      delay(10);
    }

    // comprueba si el jugador ha presionado el botón correcto
    if (secuencia[paso] != botonPresionado) {
      // si el jugador comete un error, parpadean todos los LEDs y suena el buzzer
      for (int k = 0; k < 3; k++) {
        digitalWrite(leds[k], HIGH);
        delay(200);
        digitalWrite(leds[k], LOW);
      }

      // parpadean todos los LEDs
      for (int l = 0; l < 3; l++) {
        digitalWrite(leds[l], HIGH);
      }
      delay(200);
      for (int m = 0; m < 3; m++) {
        digitalWrite(leds[m], LOW);
      }
      delay(200);

      // indica que el jugador ha perdido
      perder = true;
      // produce un sonido al perder
      tone(buzzer, 200);
      delay(200);
      noTone(buzzer);
      Serial.println("Secuencia incorrecta. Has perdido.");
      Serial.println("Reiniciando secuencia...");
      
      // reinicia el juego después de un error
      delay(3000);
      iniciarJuego();
      return; 
    }

    // incrementa el paso actual
    paso++;
  }

  // si el jugador ha repetido correctamente la secuencia
  if (!perder) {
    paso = 0;
    // genera el siguiente paso en la secuencia
    secuencia[ronda] = random(0, 3);
    ronda++;
  }
}
