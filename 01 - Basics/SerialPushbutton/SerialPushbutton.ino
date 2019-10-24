#include <PushButton.h>

PushButton btn1(2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(btn1.pressionadoPorNivel()) {
    Serial.println("Botao pressionado por NIVEL");
  }

  if(btn1.pressionadoPorPulso()) {
    Serial.println("Botao pressionado por PULSO");
  }
}
