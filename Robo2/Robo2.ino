int in1=13;
int in2=12;
int in3=11;
int in4=10;

int speedPinRight=5;
int speedPinLeft=6;

int cnt=-500;

void setup() {
  Serial.begin(9600);
  Serial.println("Setup");
  cnt=0;
  
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);  
  stopLeft();
  stopRight();
  Serial.println("Ende Setup");
}

void loop() {
  cnt++;
  delay(1);

  if(cnt<2000) {
    forwardLeft(200);
    stopRight();
  } 
  else if(cnt<4000) {
    backwardLeft(200);
    stopRight();
  }
  else if(cnt<6000) {
    forwardRight(200);
    stopLeft();
  } 
  else if(cnt<8000) {
    backwardRight(200);
    stopLeft();
  }  
  else {
    stopLeft();
    stopRight();
    cnt=8001;
  }
}

/**
 * Functions to control the motors
 */
 
void forwardLeft(int speed) {
  analogWrite(speedPinLeft, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void backwardLeft(int speed) {
  analogWrite(speedPinLeft, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void stopLeft() {
  analogWrite(speedPinLeft, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void forwardRight(int speed) {
  analogWrite(speedPinRight, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backwardRight(int speed) {
  analogWrite(speedPinRight, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopRight() {
  analogWrite(speedPinRight, 0);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
