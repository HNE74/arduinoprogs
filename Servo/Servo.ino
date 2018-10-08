#include <Servo.h>

Servo myservo;

int potpin = 2;
int val;
int sval;

void setup() {
  myservo.attach(9);
}

void loop() {
  val = analogRead(potpin);
  sval = map(val, 0, 1024, 0, 180);
  myservo.write(sval);
  delay(15);
}
