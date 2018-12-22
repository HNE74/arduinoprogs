
int in1=13;
int in2=12;
int in3=11;
int in4=10;

int speedPinRight=6;
int speedPinLeft=5;

int cmdNdx = -1;
boolean cmdRead = true;
String cmdList[10] = {"1,200,1,200,2000","0,0,1,200,2000","1,200,0,0,2000"};
int cnt=-1;
boolean finished=false;

int dirRight=0;
int dirLeft=0;
int speedRight=0;
int speedLeft=0;
int duration=0;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  Serial.begin(9600);
  Serial.println("Setup");

  stopLeft();
  stopRight();
  Serial.println("Ende Setup");
}

void loop() { 

  if(cmdNdx<=2) {
    if(cmdRead) {
      cmdNdx+=1;
      parseCommand(cmdNdx);
      cmdRead=false;
    }
    else {
      if(cnt<duration) {
        delay(1);
        processCommand();
        cnt++;
      }
      else {
        cnt=-1;
        cmdRead=true;
      }
    }
  }

  if(cmdNdx>2) {
    cmdRead=false;
    if(!finished) {
      Serial.println("Stop");
      stopLeft();
      stopRight();
      finished=true;      
    }    
  }
}

void processCommand() {
  if(dirRight == 1) {
    forwardRight(speedRight); 
  }
  else if(dirRight == 2) {
    backwardRight(speedRight);
  }
  else {
    stopRight();
  }

  if(dirLeft == 1) {
    forwardLeft(speedLeft); 
  }
  else if(dirLeft == 2) {
    backwardLeft(speedLeft);
  }
  else {
    stopLeft();
  }  
}

void parseCommand(int ndx) {
  String cmd = cmdList[ndx];
  int oldPos = -1;
  int pos = cmd.indexOf(',');
  dirRight = cmd.substring(0, pos).toInt();
  
  pos++;
  oldPos = pos;
  pos = cmd.indexOf(',', pos+1);
  speedRight = cmd.substring(oldPos, pos).toInt();  

  pos++;
  oldPos = pos;
  pos = cmd.indexOf(',', pos+1);
  dirLeft = cmd.substring(oldPos, pos).toInt(); 

  pos++;
  oldPos = pos;
  pos = cmd.indexOf(',', pos+1);
  speedLeft = cmd.substring(oldPos, pos).toInt(); 

  pos++;
  oldPos = pos;
  pos = cmd.indexOf(',', pos+1);
  duration = cmd.substring(oldPos, pos).toInt(); 

  String info = String("Command: right motor=" + String(dirRight) + "," + String(speedRight) + " left motor=" + String(dirLeft) + "," + String(speedLeft) + " duration=" + String(duration));
  Serial.println(info); 
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
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
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
