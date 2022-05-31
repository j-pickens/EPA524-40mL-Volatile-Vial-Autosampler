#include <Wire.h> // used for i2c communcation
#define SLAVE_ADDR 8 // define i2c address

const int stepX = 2; const int dirX  = 5; const int endX = 9;
const int stepY = 3; const int dirY  = 6; const int endY = 10;
const int stepZ = 4; const int dirZ  = 7; const int endZ = 11;
const int stepA = 12; const int dirA  = 13; const byte endA = 14;  //14 = A0

const int enPin = 8;
char i2command[2]; // AF###

int motorDir;

void setup() {
  Serial.begin(9600);
  Serial.println("Loading..");
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);  // Call receiveEvent when data received

  pinMode(stepX, OUTPUT); pinMode(dirX, OUTPUT); pinMode(endX, INPUT_PULLUP);
  pinMode(stepY, OUTPUT); pinMode(dirY, OUTPUT); pinMode(endY, INPUT_PULLUP);
  pinMode(stepZ, OUTPUT); pinMode(dirZ, OUTPUT); pinMode(endZ, INPUT_PULLUP);
  pinMode(stepA, OUTPUT); pinMode(dirA, OUTPUT); pinMode(endA, INPUT_PULLUP);

  digitalWrite(enPin, HIGH); // Stepper disabled
}

void loop() {
  digitalWrite(enPin, LOW);                                      // Stepper enabled
  digitalWrite(5, HIGH);                                      //enable stepper
  for (int x = 0; x < 1000; x++) {                                // increment stepper at speed
    digitalWrite(2, LOW);                                    // energize first coil
    delayMicroseconds(500);                                      // delay
    digitalWrite(2, HIGH);                                   // energize second coil
    delayMicroseconds(500);                                      // delay
  }
  digitalWrite(enPin, HIGH);                                     // disable stepper
  Serial.println("Done");
  delay(10000);
}

void receiveEvent(int howMany) {      // function that executes whenever data is received from master
  int i = 0;
  while (1 < Wire.available()) {      // loop through all but the last
    i2command[i] = Wire.read();             // receive byte as a character
    i++;
  }
  int numberValue = Wire.read();                // receive byte as an integer

  if (i2command[1] == 'F') {
    motorDir = 1;
  }
  if (i2command[1] == 'R') {
    motorDir = 0;
  }

  numberValue = numberValue * 100;
  Serial.print("moveMotor(2,5,"); Serial.print(motorDir); Serial.print(","); Serial.print(numberValue); Serial.println(")");
  delay(500);

}


//  // Move motor
//  void moveMotor(int motorDirPin, int motorStepPin, int motorDirections, int motorSteps, int motorSpeed, int endStopPin) {
//    //Serial.println("Moving Motor");
//    digitalWrite(enPin, LOW);                                               // enable stepper
//    digitalWrite(motorDirPin, motorDirections);                             // Set stepper direction 1 = Foward, 0 = Reverse
//    for (int x = 0; x < motorSteps; x++) {                                  // increment stepper at speed
//      if (digitalRead(endStopPin) != HIGH) {                                // make sure endstop isn't triggered
//        digitalWrite(motorStepPin, LOW);                                    // energize first coil
//        delayMicroseconds(motorSpeed);                                      // delay
//        digitalWrite(motorStepPin, HIGH);                                   // energize second coil
//        delayMicroseconds(motorSpeed);                                      // delay
//      }
//      else {                                                                 // endstop is triggered
//        digitalWrite(enPin, LOW);                                           // enable stepper
//        digitalWrite(motorDirPin, 1);                                       // Set stepper direction 1 = Foward, 0 = Reverse
//        while (digitalRead(endStopPin) == HIGH) {                           // Back off of endstop
//          digitalWrite(motorStepPin, LOW);                                  // energize first coil
//          delayMicroseconds(motorSpeed);                                    // delay
//          digitalWrite(motorStepPin, HIGH);                                 // energize second coil
//          delayMicroseconds(motorSpeed);                                    // delay
//        }
//        Serial.println("Done moving");
//
//        // Send endstop message to NODE-RED
//      }
//    }
//    digitalWrite(enPin, HIGH); // disable stepper
//    //update EPROM
//    //send message to NODE-RED
//  }
