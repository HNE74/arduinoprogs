const int activationPin = 9;
const int STATE_WAIT;
const int STATE_VALUE_SET;
int state = STATE_WAIT;

void setup() {
  Serial.begin(9600);
  pinMode(activationPin, INPUT);
  resetDiceValue();
}

void loop() {
  int val = digitalRead(activationPin);

  if(val == 1 && state == STATE_WAIT) {
    resetDiceValue();
    int value = random(1,7);
    showDiceValue(value);
    state = STATE_VALUE_SET;
  }
  else if(val == 0) {
    state == STATE_WAIT;
  }
}

void resetDiceValue() {
  for(int i=2;i<=7;i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void showDiceValue(int value) {
  for(int i=2;i<value+2; i++) {
    digitalWrite(i, HIGH);
  }

  Serial.println(value); 
}
