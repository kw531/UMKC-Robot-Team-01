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
  forward(1000);

  backward(1000);

  delay(1000);
  
  right(90);

  left(90);
  
  delay(5000);
}

void backward(int time){
  rightMotor->run(BACKWARD);
  leftMotor->run(BACKWARD);
  for(int i=0; i<time; i++){
    rightMotor->setSpeed(200);
    leftMotor->setSpeed(200);
  }
  cleanUp();
}

void forward (int time){
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  for(int i=0; i<time; i++){
    rightMotor->setSpeed(200);
    leftMotor->setSpeed(200);
  }
  cleanUp();
}

void left(int angle){
  int time;
  switch(angle){
      case 45:
        time=500;
        break;
      case 90:
        time=1000;
        break;
       default:
        time = 0;
    }
    
  int speed=0;
  rightMotor->run(FORWARD);
  leftMotor->run(FBACKWARD);
  for(int i=0; i<time; i++){
    if(i<200){
      speed=i;
    }else speed=200;
    rightMotor->setSpeed(speed);
    leftMotor->setSpeed(speed);
  }
  cleanUp();
}

void right(int angle){
  int time;
  switch(angle){
      case 45:
        time=500;
        break;
      case 90:
        time=1000;
        break;
       default:
        time = 0;
    }

  int speed=0;
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
  for(int i=0; i<time; i++){
    if(i<200){
      speed=i;
    }else speed=200;
    rightMotor->setSpeed(speed);
    leftMotor->setSpeed(speed);
  }
  cleanUp();
  
}
void cleanUp(){
  rightMotor->run(RELEASE);
  leftMotor->run(RELEASE);
  }

