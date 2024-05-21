import processing.serial.*;

Serial mySerial;

int lecturaPulso;

color colorPrincipal1 = color(255, 0, 0);
color colorPrincipal2 = color(100, 0, 255);

int numeroElipses = 30;

float tiempo = 0;

void setup() {
  size(600, 600);
  noStroke();

  String[] portNames = Serial.list();
  if (portNames.length == 0) {
    println("No hay puertos serial disponibles");
    return;
  }

  mySerial = new Serial(this, "/dev/cu.usbmodemF412FA6372942", 9600);
}

void draw() {
  background(0);

  if (mySerial.available() > 0) {
    lecturaPulso = mySerial.read();
  }

  float pulso = map(lecturaPulso, 0, 255, 0, min(width, height) / 1.5);

  for (int i = 0; i < numeroElipses; i++) {
    float desplazamiento = sin(tiempo + i * 0.1) * pulso;
    float cambioColor = abs(sin(tiempo + i * 0.1)); // Ajustar la velocidad de desvanecimiento

    float centroX = map(i, 0, numeroElipses - 1, width / 2, 4 * width / 2);
    float centroY = height / 2 - i * 30;

    fill(lerpColor(colorPrincipal1, colorPrincipal2, cambioColor), pulso + desplazamiento);
    ellipse(centroX, centroY, pulso + desplazamiento, pulso + desplazamiento);

    delay(5); // Retardo entre elipses (en milisegundos)
  }

  tiempo += 0.001; // Reducir la frecuencia de actualización del tiempo
}
