#define STATE_RECEIVE_COMMANDS 1
#define STATE_WAIT 2
#define STATE_HANDLE_COMMANDS 3
int state = STATE_RECEIVE_COMMANDS;

#define COMMAND_DELIMITER "X"
#define COMMAND_PARAM_DELIMITER ","
#define MAX_NUMBER_COMMANDS 10

int in1=13;
int in2=12;
int in3=11;
int in4=10;
int speedPinRight=6;
int speedPinLeft=5;

int cmdNdx = -1;
boolean cmdRead = true;
String cmdList[MAX_NUMBER_COMMANDS];
int cmdLen=-1;
int durationCnt=-1;

int dirRight=0;
int dirLeft=0;
int speedRight=0;
int speedLeft=0;
int duration=0;
int waitDuration=5000;

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);  
  Serial.begin(9600);

  stopLeft();
  stopRight();
}

void loop() { 
  if(state == STATE_RECEIVE_COMMANDS) {
    if(receiveCommands()) {
      Serial.println("STATE_WAIT");
      state = STATE_WAIT;
    }
  }
  else if(state == STATE_WAIT) {
    if(!wait()) {
      Serial.println("STATE_HANDLE_COMMANDS");
      state = STATE_HANDLE_COMMANDS;
    }
  }
  else if(state == STATE_HANDLE_COMMANDS) {
    if(!handleCommands()) {
      Serial.println("STATE_RECEIVE_COMMANDS");
      state = STATE_RECEIVE_COMMANDS;
    }
  }
}

/**
 * Returns fale if a certain number of execution cylces has been exceeded
 * otherwise false.
 */
boolean wait() {
    durationCnt++;
    delay(1);
    if(durationCnt<=waitDuration) {
      return true;
    }  

    durationCnt=-1;
    return false;
}

/**
 * Receives commands from the serial input and puts them
 * into the command array.
 * Example command sequence (forward, right, left) 2000 cycles:
 * 1,200,1,200,2000X0,0,1,200,2000X1,200,0,0,2000
 */
boolean receiveCommands() {
  int oldPos=0;
  int pos=0;
  if(Serial.available() > 0) {
    String commands = Serial.readString();
    Serial.println("Command sequence: " + commands);

    if(commands.indexOf(COMMAND_DELIMITER) == -1) {
      waitDuration=commands.toInt();
      Serial.println("Command execution wait duration set to: " + String(waitDuration));
      return false;
    }
    
    int ndx=0;
    while(pos != -1) { 
      pos=commands.indexOf(COMMAND_DELIMITER, oldPos);
      if(pos > -1 && ndx<MAX_NUMBER_COMMANDS) {
        cmdList[ndx]=commands.substring(oldPos, pos);
        oldPos=pos+1;
        Serial.println("Added command: " +  cmdList[ndx]);
      }
      else if(ndx<MAX_NUMBER_COMMANDS) {
        cmdList[ndx]=commands.substring(oldPos,commands.length());
        Serial.println("Added command: " +cmdList[ndx]);       
      }
      ndx++;
    }
    cmdLen=ndx;
    return true;
  }
  return false;
}

/**
 * Parses the commands that are contained in the command array
 * and executes them.
 */
boolean handleCommands() {
  if(cmdNdx<=cmdLen) {
    if(cmdRead) {
      cmdNdx+=1;
      parseCommand(cmdNdx);
      cmdRead=false;
    }
    else {
      if(durationCnt<duration) {
        delay(1);
        processCommand();
        durationCnt++;
      }
      else {
        durationCnt=-1;
        cmdRead=true;
      }
    }
  }

  if(cmdNdx>=cmdLen) {
    cmdRead=false;
    stopLeft();
    stopRight();
    cmdNdx=-1; 
    return false;     
  }
  return true;
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
  int pos = cmd.indexOf(COMMAND_PARAM_DELIMITER);
  dirRight = cmd.substring(0, pos).toInt();
  
  pos++;
  oldPos = pos;
  pos = cmd.indexOf(COMMAND_PARAM_DELIMITER, pos+1);
  speedRight = cmd.substring(oldPos, pos).toInt();  

  pos++;
  oldPos = pos;
  pos = cmd.indexOf(COMMAND_PARAM_DELIMITER, pos+1);
  dirLeft = cmd.substring(oldPos, pos).toInt(); 

  pos++;
  oldPos = pos;
  pos = cmd.indexOf(COMMAND_PARAM_DELIMITER, pos+1);
  speedLeft = cmd.substring(oldPos, pos).toInt(); 

  pos++;
  oldPos = pos;
  pos = cmd.indexOf(COMMAND_PARAM_DELIMITER, pos+1);
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
