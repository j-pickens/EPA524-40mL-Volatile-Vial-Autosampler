// Define pin connections & motor's steps per revolution
#include <Wire.h> // used for i2c communcation 
#define SLAVE_ADDR 8 // define i2c address
const int stepsPerRevolution = 2000;
char i2command[2]; // AF###
int motorDir;
int incomingByte;

void setup()
{
  // Declare pins as Outputs
  Serial.begin(9600);
  Serial.println("Loading..");
  Wire.begin(SLAVE_ADDR);

  Wire.onReceive(receiveEvent);  // Call receiveEvent when data received
  pinMode(2, OUTPUT); //X
  pinMode(5, OUTPUT); //X
  pinMode(9, INPUT_PULLUP); //X


  pinMode(3, OUTPUT); //Y
  pinMode(6, OUTPUT); //Y
  pinMode(10, INPUT_PULLUP); //Y

  pinMode(4, OUTPUT); //Z
  pinMode(7, OUTPUT); //Z
  pinMode(11, INPUT_PULLUP); //Z

  pinMode(12, OUTPUT); //A
  pinMode(13, OUTPUT); //A
  pinMode(17, INPUT_PULLUP); //A A03

  pinMode(8, OUTPUT); // Enable
  digitalWrite(8, HIGH);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    moveMotorFun(2, 5, 1, 10, 9);
    Serial.available() == 0;
  }
  delay(500);
}

void moveMotorFun(int setPin, int dirPin, int motorDir, int revolutionStep, int endPin) {
  digitalWrite(8, LOW);                           // enable steppers
  digitalWrite(dirPin, motorDir);                     // Set motor direction clockwise
  for (int x = 0; x < revolutionStep; x++) {      // spin
    if (digitalRead(11) != HIGH) {                                // make sure endstop isn't triggered
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
}

void receiveEvent(int howMany) {      // function that executes whenever data is received from master
  int i = 0;
  while (1 < Wire.available()) {      // loop through all but the last
    i2command[i] = Wire.read();             // receive byte as a character
    i++;
  }
  int numberValue = Wire.read();                // receive byte as an integer

  if (i2command[1] == 'F') {                    // XF100
    motorDir = 1;
  }
  if (i2command[1] == 'R') {
    motorDir = 0;
  }

  numberValue = numberValue * 100;
  Serial.print("moveMotor("); Serial.print(i2command[0]); Serial.print(","); Serial.print(motorDir); Serial.print(","); Serial.print(numberValue); Serial.println(")");
  delay(500);

  switch (i2command[0]) {
    case ('X'):
      moveMotorFun(2, 5, motorDir, numberValue, 9);
      break;
    case ('Y'):
      moveMotorFun(3, 6, motorDir, numberValue, 10);
      break;
    case ('Z'):
      moveMotorFun(4, 7, motorDir, numberValue, 11);
      break;
    case ('A'):
      moveMotorFun(12, 13, motorDir, numberValue, 17);
      break;
  }

}
