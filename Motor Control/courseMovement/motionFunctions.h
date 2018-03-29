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

  AFMSc.begin();  // Motorsheild setup for the conveyor

  cnvyr1->setSpeed(255);
  cnvyr1->run(FORWARD);
  cnvyr1->run(RELEASE);
  cnvyr2->setSpeed(255);
  cnvyr2->run(FORWARD);
  cnvyr2->run(RELEASE);
}

void driversSetup() {

  AFMSd.begin();  // Motorsheild setup for driving

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

void leftEncoderEvent() {
  // Left encoder interrupt
  leftCount++;
}

void rightEncoderEvent() {
  // Right encoder interrupt
  rightCount++;
}

void motionSetup() {
  // Calls all the setup functions for the systems
  Serial.begin(9600);           // set up Serial library at 9600 bps
  encoderSetup();
  IMUSetup();
  conveyorSetup();
  driversSetup();
}

void runConveyor() {
  // Turn on the Conveyor
  int speed = 255; // Cannot be lower than this or conveyor doesn't move
  cnvyr1->run(BACKWARD);
  cnvyr2->run(BACKWARD);

  cnvyr1->setSpeed(speed);
  cnvyr2->setSpeed(speed);
}

void stopConveyor(){
    // Turn off the Conveyor
  int speed = 0; // Cannot be lower than this or conveyor doesn't move
  cnvyr1->run(BACKWARD);
  cnvyr2->run(BACKWARD);

  cnvyr1->setSpeed(speed);
  cnvyr2->setSpeed(speed);
}

void forward (int dist) {
  // Robot moves distance (inches) forward
  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  moveRobot(dist);

  cleanUp();
}

void backward (int dist) {
  // Robot moves distance (inches) backwards
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);

  moveRobot(dist);

  cleanUp();
}

void moveRobot(int dist) {
  // Move the robot in inches
  int driveSpeed = 150;

  leftCount = 0; // Reset the encoder counts
  rightCount = 0;
  unsigned long ticks;

  ticks = dist * 229; //229 ticks per inch
  do {
    rightMotorFront->setSpeed(driveSpeed);
    rightMotorRear->setSpeed(driveSpeed);
    leftMotorFront->setSpeed(driveSpeed);
    leftMotorRear->setSpeed(driveSpeed);
  } while (((leftCount + rightCount) / 2) < ticks); // Average the encoder count
}

void left(float angle) {
  // Turns the robot left to an angle of degrees.
  // turning left = higher angle on IMU

  IMUreset(); // Zero the IMU before turning
  float IMUangle = 0;
  int speed;
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  sensors_event_t event; // Get the angle from the IMU
  bno.getEvent(&event);
  IMUangle = event.orientation.x;

  Serial.print("\tLeft turn X: "); // Issue tracking printout
  Serial.print(event.orientation.x, 2);
  Serial.println("");

  while (IMUangle > 360.0 - angle || IMUangle < 3.0) {
    //sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x; // Get new IMU angle

    if (IMUangle < 360.0 - (angle - (angle * .05))) {
      // Reduce speed as we get closer to
      speed = 80;
      rightMotorFront->setSpeed(speed + 20); // Laggy motor, gets a boost
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    } else {
      speed = 150;
      rightMotorFront->setSpeed(speed + 20); // Laggy motor, gets a boost
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    }
  }
  cleanUp();
}

void right(float angle) {
  // Turns the robot right to a specific angle
  // Turning right = smaller angle on IMU
  IMUreset(); // Zero the IMU
  int IMUangle = 0;
  int speed;

  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);

  sensors_event_t event;
  bno.getEvent(&event);
  IMUangle = event.orientation.x; // Get IMU angle

  while (IMUangle < (angle) || IMUangle >= 359) {
    //sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x; // Get IMU angle

    if (IMUangle >= (angle - (angle * .1))) {
      // Reduce speed as we get closer
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

void still(int sec) {
  cleanUp(); //Make sure motors are not running
  sec = sec * 1000; //delay works in mili
  delay(sec);
}


void cleanUp() {
  // RELEASE THE MOTORS
  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);
}

void conveyorCleanUp() {
  // Not used currently, but preparation for turning off the conveyor when we don't need it.
  cnvyr1->run(RELEASE);
  cnvyr2->run(RELEASE);
}

void IMUreset() {
  // Resets the IMU so that the calibration is zero after a turn
  bno.begin();
  delay(700);
}

#endif





