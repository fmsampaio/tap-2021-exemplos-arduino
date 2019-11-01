
#include <Ultrasonic.h>

#define TRIGGER_PIN  8
#define ECHO_PIN     7

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup()
  {
  Serial.begin(9600);
  }

void loop()
  {
  float cmMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);

  Serial.print("CM: ");
  Serial.println(cmMsec);
  delay(1000);
  }
