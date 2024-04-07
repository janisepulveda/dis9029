// arreglo para almacenar la secuencia de luces que se mostrarán al jugador
int secuencia[100];
// variable para realizar un seguimiento de la ronda actual del juego
int ronda = 0;
// variable para realizar un seguimiento del paso actual dentro de una ronda
int paso = 0;
// leds verde, amarillo, azul y rojo
int leds[4] = { 2, 3, 4, 5 };
// botones verde, amarillo, azul y rojo, pines análogos
int botones[4] = { A2, A3, A4, A5 }; 
// variable que almacena el índice del botón que el jugador ha presionado
int botonPresionado = 0;
// variable que indica si el jugador ha perdido el juego
int perder = false;
// pin al que está conectado el buzzer
int buzzer = 6;
// arreglo que contiene los tonos correspondientes a los leds
int sonidos[4] = { 400, 450, 500, 550 };

void setup() {
  // configura el pin del buzzer como salida
  pinMode(buzzer, OUTPUT);
  // produce un tono en el buzzer
  tone(buzzer, sonidos[2]);
  // espera un breve periodo de tiempo
  delay(20);
  // detiene el tono del buzzer
  noTone(buzzer);
  // configura los pines de los LEDs como salidas
  for (int i = 0; i <= 3; i++) {
    pinMode(leds[i], OUTPUT);
  }

  // configura los pines de los botones como entradas
  for (int i = 0; i <= 3; i++) {
    pinMode(botones[i], INPUT);
  }
  // inicia la semilla del generador de números aleatorios
  randomSeed(analogRead(0));
  
  // melodía al iniciar el juego
  tone(buzzer, 500);
  delay(200);
  tone(buzzer, 600);
  delay(200);
  tone(buzzer, 700);
  delay(200);
  noTone(buzzer);
  // encendido de los LEDs al iniciar el juego
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
  }
  delay(500);
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  // si el jugador ha perdido el juego, reinicia el arreglo que almacena la secuencia, el número de ronda, el paso y la variable de pérdida
  if (perder) {
    int secuencia[100];
    ronda = 0;       // reinicia el número de ronda
    paso = 0;        // reinicia el paso
    perder = false;  // reinicia la variable de pérdida
  }

  // si es la primera ronda del juego, enciende los LEDs durante un breve periodo de tiempo y luego apágalos
  if (ronda == 0) {
    digitalWrite(leds[0], HIGH);
    digitalWrite(leds[1], HIGH);
    digitalWrite(leds[2], HIGH);
    digitalWrite(leds[3], HIGH);
    delay(424);
    digitalWrite(leds[0], LOW);
    digitalWrite(leds[1], LOW);
    digitalWrite(leds[2], LOW);
    digitalWrite(leds[3], LOW);
    delay(242);
  }

  // genera un número aleatorio y agrégalo a la secuencia
  secuencia[ronda++] = random(0, 4);

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
      for (int i = 0; i <= 3; i++) {
        if (analogRead(botones[i]) > 900) { // selecciona un umbral adecuado según la resistencia pull-down
          botonPresionado = i;
          digitalWrite(leds[i], HIGH);
          // enciende el buzzer con la misma frecuencia que el LED
          tone(buzzer, sonidos[i]);
          delay(300);
          digitalWrite(leds[i], LOW);
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
      for (int i = 0; i <= 3; i++) {
        digitalWrite(leds[i], HIGH);
        delay(200);
        digitalWrite(leds[i], LOW);
      }

      // parpadean todos los LEDs dos veces
      for (int i = 0; i <= 3; i++) {
        digitalWrite(leds[0], HIGH);
        digitalWrite(leds[1], HIGH);
        digitalWrite(leds[2], HIGH);
        digitalWrite(leds[3], HIGH);
        delay(100);
        digitalWrite(leds[0], LOW);
        digitalWrite(leds[1], LOW);
        digitalWrite(leds[2], LOW);
        digitalWrite(leds[3], LOW);
        delay(100);
      }

      // indica que el jugador ha perdido
      perder = true;
      // produce un sonido al perder
      tone(buzzer, 200);
      delay(100);
      noTone(buzzer);
    }

    // si el jugador ha perdido, sal del bucle
    if (perder) {
      break;
    }
    // incrementa el paso actual
    paso++;
  }

  // reinicia el paso
  paso = 0;
  // espera un segundo antes de comenzar la siguiente ronda
  delay(1000);
}
