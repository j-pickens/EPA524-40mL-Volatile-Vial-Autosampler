
#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
  Serial.println("Loading...");
}

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  int ABCStepper = random(1, 5);
  char stepperMotor;
  if (ABCStepper == 1) {
    stepperMotor = 'X';
  }
  if (ABCStepper == 2) {
    stepperMotor = 'Y';
  }
  if (ABCStepper == 3) {
    stepperMotor = 'Z';
  }
  if (ABCStepper == 4) {
    stepperMotor = 'A';
  }


  int radDir = random(0, 2);
  char stepperDir;
  if (radDir == 1) {
    stepperDir = 'F';
  }
  if (radDir == 0) {
    stepperDir = 'R';
  }

  int stepperSteps = random(1, 150);

  Wire.write(stepperMotor);          // sends five bytes
  Wire.write(stepperDir);            // sends five bytes
  Wire.write(stepperSteps);          // send one bite
  Wire.endTransmission();           // stop transmitting

  Serial.print(stepperMotor);
  Serial.print(stepperDir);
  Serial.println(stepperSteps);

  
  Serial.print("0x"); Serial.print(stepperMotor, HEX); Serial.print(' '); 
  Serial.print("0x"); Serial.print(stepperDir, HEX); Serial.print(' ');
  Serial.print("0x"); Serial.println(stepperSteps, HEX);


  delay(5000);
}
