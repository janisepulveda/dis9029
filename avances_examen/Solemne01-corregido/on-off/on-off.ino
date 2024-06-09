const int buttonPin = A2; // Pin del botón (analógico A2)
const int ledPin = 2;     // Pin del LED (digital 2)

int buttonState = 0;      // Variable para almacenar el estado del botón
int lastButtonState = LOW; // Variable para almacenar el último estado del botón
bool ledEncendido = false; // Variable para almacenar el estado del LED

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin); // Lee el estado actual del botón

  // Si el estado del botón ha cambiado
  if (buttonState != lastButtonState) {
    // Si el nuevo estado del botón es alto (se ha presionado)
    if (buttonState == HIGH) {
      // Cambia el estado del LED
      ledEncendido = !ledEncendido;
      // Actualiza el estado del LED
      digitalWrite(ledPin, ledEncendido ? HIGH : LOW);
    }
    // Actualiza el último estado del botón
    lastButtonState = buttonState;
  }

  delay(50);
}
