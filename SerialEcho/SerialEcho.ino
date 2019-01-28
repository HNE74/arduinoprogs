void setup() {
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    Serial.write(Serial.read());
  }
}
