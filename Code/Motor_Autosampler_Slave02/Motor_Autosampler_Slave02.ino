//-------------------------------------------------------------------------
// 2022/05/15
//
// S James Parsons Jr
// www.sjamesparsonsjr.com
//
//-------------------------------------------------------------------------



//-------------------------------------------------------------------------
// +++ Libraries +++
#include <Wire.h> // used for i2c communcation 

//-------------------------------------------------------------------------
// +++ Variables +++
#define SLAVE_ADDR 8 // define i2c address
//const int stepsPerRevolution = 2000;
char i2command[5]; // AF###
int motorDir;
int incomingByte;
int setPin;
int dirPin;
int endStop;
//-------------------------------------------------------------------------
// +++ Functions +++
void moveMotorFun(char motor, char motorDir, long revolutionStep) {

  switch (motor) {
    case ('X'):
      setPin = 2;
      dirPin = 5;
      endStop = 9;
      break;
    case ('Y'):
      setPin = 3;
      dirPin = 6;
      endStop = 10;
      break;
    case ('Z'):
      setPin = 4;
      dirPin = 7;
      endStop = 11;
      break;
    case ('A'):
      setPin = 12;
      dirPin = 13;
      endStop = 17;
      break;
  }

  if (i2command[1] == 'F') {                        // F = Forward/HIGH
    motorDir = 1;
  }
  if (i2command[1] == 'R') {                        // R = Backward/LOW
    motorDir = 0;
  }

  digitalWrite(8, LOW);                             // enable steppers
  digitalWrite(dirPin, motorDir);                   // Set motor direction clockwise
  for (int x = 0; x < revolutionStep; x++) {        // spin
    if (digitalRead(11) != HIGH) {                  // make sure endstop isn't triggered
      digitalWrite(setPin, HIGH);                   // energize first coil
      delayMicroseconds(100);                       // delay
      digitalWrite(setPin, LOW);                    // energize second coil
      delayMicroseconds(100);                       // delay
    }
    else {
      digitalWrite(dirPin, ~motorDir);                // Set motor direction clockwise
      while (digitalRead(11) == HIGH) {
        digitalWrite(setPin, HIGH);                   // energize first coil
        delayMicroseconds(100);                       // delay
        digitalWrite(setPin, LOW);                    // energize second coil
        delayMicroseconds(100);                       // delay
      }
    }
  }
  digitalWrite(8, HIGH);                          // disable steppers
  Serial.println("Done");
}

void receiveEvent(int howMany) {      // function that executes whenever data is received from master
  int i = 0;
  while (1 < Wire.available()) {      // loop through all but the last
    i2command[i] = Wire.read();             // receive byte as a character
    Serial.println(i2command[i]);     // ??? Does it always forget the last byte?
    i++;
  }
  Serial.println(Wire.read());        // Char F is the finish command.

  int thousands = ((i2command[2] - 48) * 1000);
  int hundreds = ((i2command[3] - 48) * 100);
  int tens = ((i2command[4] - 48) * 10);
  int ones = (i2command[5] - 48);

  int numberValue = (thousands + hundreds + tens + ones) ;    // receive byte as an integer

  moveMotorFun(i2command[0], i2command[1], numberValue);
  delay(500);
}

//-------------------------------------------------------------------------
// +++ Setup +++
void setup() {
  // Declare pins as Outputs
  Serial.begin(9600);
  Serial.println("Loading..");
  Wire.begin(SLAVE_ADDR);

  pinMode(2, OUTPUT);            // X
  pinMode(5, OUTPUT);            // X
  pinMode(9, INPUT_PULLUP);      // X


  pinMode(3, OUTPUT);            // Y
  pinMode(6, OUTPUT);            // Y
  pinMode(10, INPUT_PULLUP);     // Y

  pinMode(4, OUTPUT);            // Z
  pinMode(7, OUTPUT);            // Z
  pinMode(11, INPUT_PULLUP);     // Z

  pinMode(12, OUTPUT);           // A
  pinMode(13, OUTPUT);           // A
  pinMode(17, INPUT_PULLUP);     // A A03

  pinMode(8, OUTPUT);            // Enable
  digitalWrite(8, HIGH);         // Steppers disabled

  Wire.onReceive(receiveEvent); // register event
}


//-------------------------------------------------------------------------
// +++ Loop +++
void loop() {
  delay(500);
}
