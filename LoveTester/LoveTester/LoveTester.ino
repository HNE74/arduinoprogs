const int sensorPin = A0;
const float baselineTemp = 20.0;
float oldTemperature = 0.0;


void setup() {  
  Serial.begin(9600);
  for(int i=2; i<5; i++) {
    pinMode(i, OUTPUT);  
    digitalWrite(i, LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  float voltage = (sensorVal / 1024.0) * 5.0;
  float temperature = (voltage - 0.5) * 100;
  if(abs(oldTemperature-temperature) > 1) {
    Serial.print("Sensor value:");
    Serial.print(sensorVal);  
    Serial.print(", Volts: ");
    Serial.print(voltage);
    Serial.print(", Degrees C: ");
    Serial.println(temperature);
    oldTemperature = temperature;
  }

  
  if(temperature < baselineTemp) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if(temperature < baselineTemp+2) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if(temperature < baselineTemp+4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  }
  else if(temperature < baselineTemp+6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }
}
