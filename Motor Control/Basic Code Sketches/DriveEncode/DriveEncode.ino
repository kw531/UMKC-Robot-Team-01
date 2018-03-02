#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMSc = Adafruit_MotorShield(0x60); // Conveyor
Adafruit_MotorShield AFMSd = Adafruit_MotorShield(0x61); // Drive

// Conveyor Motors
Adafruit_DCMotor *cnvyr1 = AFMSc.getMotor(3);
Adafruit_DCMotor *cnvyr2 = AFMSc.getMotor(4);

// Drive Motors
Adafruit_DCMotor *rightMotorFront = AFMSd.getMotor(4);
Adafruit_DCMotor *rightMotorRear = AFMSd.getMotor(3);
Adafruit_DCMotor *leftMotorFront = AFMSd.getMotor(1);
Adafruit_DCMotor *leftMotorRear = AFMSd.getMotor(2);

//Encoders
#define RH_ENCODER_A 19
#define RH_ENCODER_B 46
#define LH_ENCODER_A 18
#define LH_ENCODER_B 44

// variables to store the number of encoder pulses
// for each motor
volatile unsigned long leftCount = 0;
volatile unsigned long rightCount = 0;

//void forward(int time);
//void backward(int time);
//void left(int angle);
//void right(int angle);
//void cleanUp();

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

// Encoder Setup
  pinMode(LH_ENCODER_A, INPUT);
  pinMode(LH_ENCODER_B, INPUT);
  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);
  
  // initialize hardware interrupts
  attachInterrupt(5, leftEncoderEvent, CHANGE);
  attachInterrupt(4, rightEncoderEvent, CHANGE);

// Conveyor Setup
  AFMSc.begin();  // create with the default frequency 1.6KHz
  
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
  
// Drive Setup
  AFMSd.begin();  // create with the default frequency 1.6KHz

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



forward(29);

delay(5000);

backward(29);

delay(5000);

}

// encoder event for the interrupt call
void leftEncoderEvent() {
  leftCount++;
//  if (digitalRead(LH_ENCODER_A) == HIGH) {
//    if (digitalRead(LH_ENCODER_B) == LOW) {
//      leftCount--;
//    } else {
//      leftCount++;
//    }
//  } else {
//    if (digitalRead(LH_ENCODER_B) == LOW) {
//      leftCount++;
//    } else {
//      leftCount--;
//    }
//  }
}
 
// encoder event for the interrupt call
void rightEncoderEvent() {
  rightCount++;
//  if (digitalRead(RH_ENCODER_A) == HIGH) {
//    if (digitalRead(RH_ENCODER_B) == LOW) {
//      rightCount++;
//    } else {
//      rightCount--;
//    }
//  } else {
//    if (digitalRead(RH_ENCODER_B) == LOW) {
//      rightCount--;
//    } else {
//      rightCount++;
//    }
//  }
}

void backward(int dist) {
  // Reset the encoder count
  leftCount=0;
  rightCount=0;
  unsigned long ticks;

  ticks = dist * 229; //229 ticks per inch
  
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);
  do{
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  }while(((leftCount+rightCount)/2)<ticks);
  
  cleanUp();
}

void forward (int dist) {
  // Reset the encoder count
  leftCount=0;
  rightCount=0;
  unsigned long ticks;

  ticks = dist * 229; //229 ticks per inch
  
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);
  do{
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  }while(((leftCount+rightCount)/2)<ticks);
  
  cleanUp();
}
//
//void left(int angle) {
//  int time;
//  switch (angle) {
//    case 45:
//      time = 400;
//      break;
//    case 90:
//      time = 750;
//      break;
//    default:
//      time = 0;
//  }
//
//  int speed = 0;
//  rightMotorFront->run(FORWARD);
//  rightMotorRear->run(FORWARD);
//  leftMotorFront->run(BACKWARD);
//  leftMotorRear->run(BACKWARD);
//  for (int i = 0; i < time; i++) {
//    if (i < 200) {
//      speed = i;
//    } else speed = 200;
//    rightMotorFront->setSpeed(speed);
//    rightMotorRear->setSpeed(speed);
//    leftMotorFront->setSpeed(speed);
//    leftMotorRear->setSpeed(0);
//  }
//  cleanUp();
//}
//
//void right(int angle) {
//  int time;
//  switch (angle) {
//    case 45:
//      time = 370;
//      break;
//    case 90:
//      time = 730;
//      break;
//    default:
//      time = 0;
//  }
//
//  int speed = 0;
//  rightMotorFront->run(BACKWARD);
//  rightMotorRear->run(BACKWARD);
//  leftMotorFront->run(FORWARD);
//  leftMotorRear->run(FORWARD);
//  for (int i = 0; i < time; i++) {
//    if (i < 200) {
//      speed = i;
//    } else speed = 200;
//    rightMotorFront->setSpeed(speed);
//    rightMotorRear->setSpeed(0);
//    leftMotorFront->setSpeed(speed);
//    leftMotorRear->setSpeed(speed);
//  }
//  cleanUp();
//
//}
void cleanUp() {
  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);
}

