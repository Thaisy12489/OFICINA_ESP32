#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Dino-Thaisy", "Oficina", 100);

const int TRIG = 5;
const int ECHO = 18;

const int DISTANCIA_PULO = 15;       // cm: abaixo disso conta como mão detectada
const unsigned long INTERVALO = 400; // ms entre pulos

unsigned long ultimoPulo = 0;

float lerDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 30000);
  if (duracao == 0) return 999;
  return duracao * 0.0343 / 2;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  bleKeyboard.begin();
}

void loop() {
  float d = lerDistancia();
  Serial.println(d);

  if (bleKeyboard.isConnected()) {
    if (d < DISTANCIA_PULO && millis() - ultimoPulo > INTERVALO) {
      bleKeyboard.write(' ');   // aperta a barra de espaço
      ultimoPulo = millis();
    }
  }
  delay(30);
}