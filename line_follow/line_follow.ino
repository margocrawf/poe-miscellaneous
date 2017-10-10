#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotorRight = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorLeft = AFMS.getMotor(2);
// pins:
const int analogrightPin = A0;  // Analog right pin 
const int analogleftPin = A1; // Analog left pin

int sensorValueright = 0; // value read from the right pot
int sensorValueleft = 0; // value read from the left pot
int threshold = 20;

int TERMINAL_CHAR = 59; //ascii value of ;

int motorSpeed; //speed of the motor

/*
 * Setup
 */
void setup() {
  // start the serial
  Serial.begin(9600);
  Serial.flush();
  AFMS.begin();
  myMotorRight->setSpeed(255);
  myMotorLeft->setSpeed(255);
}

/*
 * Reassign variables if necessary,
 * from a string of the form
 * "variable_name=value;"
 */
void assign_var(String inputString) {
//  // first part of string, before equal sign
//   char* varName = strtok(inputString.c_str(), "=");
//   Serial.println(varName);
//   // if you're assigning motorSpeed
//   if (strcmp(varName, "motorSpeed") == 0) {
//      // get the thing on other side of equal sign
//      char* val = strtok(NULL, ";");
//      Serial.print("Changing motor speed to ");
//      Serial.println(val);
//      //assign the value
//      motorSpeed = atoi(val);
//   }
}

/*
 * Move the motor based on sensor input and
 * whatever else determines it.
 */
void move_motor(int sensorValueright, int sensorValueleft) {
  if ((sensorValueright - sensorValueleft) > threshold){
    myMotorRight->setSpeed(0);
    myMotorLeft->setSpeed(255);
  }
  else if ((sensorValueright - sensorValueleft) < -threshold){
    myMotorRight->setSpeed(255);
    myMotorLeft->setSpeed(0);
  } else {
    myMotorRight->setSpeed(255);
    myMotorLeft->setSpeed(255);
  }
  
  return;
}

/*
 * Loop 5evr
 */
void loop() {
  // read the analog in value
  sensorValueleft = analogRead(analogleftPin);
  sensorValueright = analogRead(analogrightPin);
  Serial.println(sensorValueleft);
  Serial.println(sensorValueright);
  // move the motor
  move_motor(sensorValueright, sensorValueleft);
  // if there's stuff on the serial port
  if (Serial.available() > 0) {
     // read the serial input
     String serialInput = Serial.readString();
     //assign values based on it
     assign_var(serialInput);
     
  }
  Serial.flush();
  delay(100);
  for (int i = 0; i < 100; i++){
    myMotorRight->run(FORWARD);
    myMotorLeft->run(FORWARD);
  }
}
