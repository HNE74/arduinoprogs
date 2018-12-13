int in1=13;
int in2=12;
int in3=11;
int in4=10;

int speedPinA=6;
int speedPinB=5;

int cnt=-500;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  cnt=0;
  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  _mSetSpeed(speedPinA, 200);
  _mSetSpeed(speedPinB, 200);  
  _mStop(in1, in2);
  _mStop(in3, in4);
  Serial.println("Ende Setup");
}

void loop() {
  cnt++;
  delay(1);

  if(cnt<2000) {
    _mRight(in1, in2);
    _mRight(in3, in4);  
  } else if (cnt<4000) {
    _mRight(in1, in2);
    _mStop(in3, in4);
  } else if (cnt<6000) {
    _mRight(in3, in4);
    _mStop(in1, in2);
  } else if (cnt<8000) {
    _mLeft(in1, in2);
    _mLeft(in3, in4);    
  } else if (cnt>=10000) {
    _mStop(in1, in2);
    _mStop(in3, in4);  
    cnt=10001; 
  }
  
}

void _mRight(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void _mLeft(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void _mStop(int pin1, int pin2) {
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,HIGH);
}

void _mSetSpeed(int pwmPin, int speed) {
  analogWrite(pwmPin, speed);
}
