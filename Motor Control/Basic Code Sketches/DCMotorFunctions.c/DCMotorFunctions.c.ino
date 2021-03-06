#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
// Or, create it with a different I2C address (say for stacking)
 Adafruit_MotorShield AFMSc = Adafruit_MotorShield(0x60); // Conveyor
 Adafruit_MotorShield AFMSd = Adafruit_MotorShield(0x61); // Drive

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *cnvyr1 = AFMSc.getMotor(3);
Adafruit_DCMotor *cnvyr2 = AFMSc.getMotor(4);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotorFront = AFMSd.getMotor(4);
Adafruit_DCMotor *rightMotorRear = AFMSd.getMotor(3);
Adafruit_DCMotor *leftMotorFront = AFMSd.getMotor(1);
Adafruit_DCMotor *leftMotorRear = AFMSd.getMotor(2);

void forward(int time);
void backward(int time);
void left(int angle);
void right(int angle);
void cleanUp();


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  AFMSc.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  cnvyr1->setSpeed(150);
  cnvyr1->run(FORWARD);
  // turn on motor
  cnvyr1->run(RELEASE);
    // Set the speed to start, from 0 (off) to 255 (max speed)
  cnvyr2->setSpeed(150);
  cnvyr2->run(FORWARD);
  // turn on motor
  cnvyr2->run(RELEASE);
  

  AFMSd.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotorFront->setSpeed(150);
  rightMotorRear->setSpeed(150);
  leftMotorFront->setSpeed(150);
  leftMotorRear->setSpeed(150);
  
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  // turn on motor
  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);


}

void loop() {
 forward(1000);
//  delay(2);
//  backward(1000);
//  delay(2);
//  left(45);
//  delay(2);
//  right(45);
//  delay(5);

  cnvyr1->run(FORWARD);
  cnvyr2->run(BACKWARD);
  
  cnvyr1->setSpeed(255);
  cnvyr2->setSpeed(255);
}

void backward(int time) {
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);
  for (int i = 0; i < time; i++) {
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  }
  cleanUp();
}

void forward (int time) {
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);
  for (int i = 0; i < time; i++) {
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  }
  cleanUp();
}

void left(int angle) {
  int time;
  switch (angle) {
    case 45:
      time = 400;
      break;
    case 90:
      time = 750;
      break;
    default:
      time = 0;
  }

  int speed = 0;
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);
  for (int i = 0; i < time; i++) {
    if (i < 200) {
      speed = i;
    } else speed = 200;
    rightMotorFront->setSpeed(speed);
    rightMotorRear->setSpeed(speed);
    leftMotorFront->setSpeed(speed);
    leftMotorRear->setSpeed(0);
  }
  cleanUp();
}

void right(int angle) {
  int time;
  switch (angle) {
    case 45:
      time = 370;
      break;
    case 90:
      time = 730;
      break;
    default:
      time = 0;
  }

  int speed = 0;
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);
  for (int i = 0; i < time; i++) {
    if (i < 200) {
      speed = i;
    } else speed = 200;
    rightMotorFront->setSpeed(speed);
    rightMotorRear->setSpeed(0);
    leftMotorFront->setSpeed(speed);
    leftMotorRear->setSpeed(speed);
  }
  cleanUp();

}
void cleanUp() {
  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);
}

