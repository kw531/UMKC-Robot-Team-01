#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);

void forward(int time);
void backward(int time);
void left(int angle);
void right(int angle);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(150);
  leftMotor->setSpeed(150);
  
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);


}

void loop() {
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(100);
  leftMotor->setSpeed(100);

}
