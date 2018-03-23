#ifndef MOTIONFUNCTIONS_H
#define MOTIONFUNCTIONS_H
#include "motion.h"

void encoderSetup() {
  // Encoder Setup
  pinMode(LH_ENCODER_A, INPUT);
  pinMode(LH_ENCODER_B, INPUT);
  pinMode(RH_ENCODER_A, INPUT);
  pinMode(RH_ENCODER_B, INPUT);

  // initialize hardware interrupts
  attachInterrupt(5, leftEncoderEvent, CHANGE);
  attachInterrupt(4, rightEncoderEvent, CHANGE);
}

void IMUSetup() {
  //IMU setup
  Serial.println("Do not destory humanity, not even once, not even as a joke"); Serial.println("");

  if (!bno.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);

  bno.setExtCrystalUse(true);
}

void conveyorSetup() {

  AFMSc.begin();  // create with the default frequency 1.6KHz

  cnvyr1->setSpeed(150);
  cnvyr1->run(FORWARD);
  cnvyr1->run(RELEASE);
  cnvyr2->setSpeed(150);
  cnvyr2->run(FORWARD);
  cnvyr2->run(RELEASE);
}

void driversSetup() {

  AFMSd.begin();  // create with the default frequency 1.6KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  int driveSpeed = 200;
  rightMotorFront->setSpeed(driveSpeed);
  rightMotorRear->setSpeed(driveSpeed);
  leftMotorFront->setSpeed(driveSpeed);
  leftMotorRear->setSpeed(driveSpeed);

  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);
}

// encoder event for the interrupt call
void leftEncoderEvent() {
  leftCount++;
}

// encoder event for the interrupt call
void rightEncoderEvent() {
  rightCount++;
}

void motionSetup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  encoderSetup();
  IMUSetup();
  conveyorSetup();
  driversSetup();
}

void runConveyor() {
  cnvyr1->run(FORWARD);
  cnvyr2->run(BACKWARD);

  cnvyr1->setSpeed(255);
  cnvyr2->setSpeed(255);
}

void forward (int dist) {
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  moveRobot(dist);

  cleanUp();
}

void backward (int dist) {
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);

  moveRobot(dist);

  cleanUp();
}

void moveRobot(int dist) {
  // Reset the encoder count
  int driveSpeed = 150;
  leftCount = 0;
  rightCount = 0;
  unsigned long ticks;

  ticks = dist * 229; //229 ticks per inch
  do {
    rightMotorFront->setSpeed(driveSpeed);
    rightMotorRear->setSpeed(driveSpeed);
    leftMotorFront->setSpeed(driveSpeed);
    leftMotorRear->setSpeed(driveSpeed);
  } while (((leftCount + rightCount) / 2) < ticks);
}
//
void left(float angle) {
  // turning left = higher angle on IMU
  IMUreset();
  float IMUangle = 0;
  int speed;
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  sensors_event_t event;
  bno.getEvent(&event);
  IMUangle = event.orientation.x;

  Serial.print("\tLeft turn X: ");
  Serial.print(event.orientation.x, 2);
  Serial.println("");
  while (IMUangle > 360.0 - angle || IMUangle < 3.0) {
    sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x;

    if (IMUangle < 360.0 - (angle - (angle * .05))) {
      speed = 80;
      rightMotorFront->setSpeed(100);
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    } else {
      speed = 150;
      rightMotorFront->setSpeed(170);
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    }
  }
  cleanUp();
}


void right(int angle) {
  // Turning right = smaller angle on IMU
  IMUreset();
  int IMUangle = 0;
  int speed;
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);

  sensors_event_t event;
  bno.getEvent(&event);
  IMUangle = event.orientation.x;

  while (IMUangle < (angle) || IMUangle >= 359) {
    sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x;

    if (IMUangle >= (angle - (angle * .1))) {
      speed = 100;
      rightMotorFront->setSpeed(speed);
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    }
    else
    {
      speed = 150;
      rightMotorFront->setSpeed(speed);
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    }
  }
  cleanUp();
}


void cleanUp() {
  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);
}

void IMUreset() {
  // Resets the IMU so that the calibration is zero after a turn
  bno.begin();
  delay(750);
}

#endif


