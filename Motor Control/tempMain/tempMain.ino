#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// IMU
Adafruit_BNO055 bno = Adafruit_BNO055(55);

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMSc = Adafruit_MotorShield(0x60); // Conveyor
Adafruit_MotorShield AFMSd = Adafruit_MotorShield(0x61); // Drive

// Conveyor Motors
Adafruit_DCMotor *cnvyr1 = AFMSc.getMotor(3);
Adafruit_DCMotor *cnvyr2 = AFMSc.getMotor(4);

// Drive Motors
Adafruit_DCMotor *rightMotorFront = AFMSd.getMotor(2);
Adafruit_DCMotor *rightMotorRear = AFMSd.getMotor(3);
Adafruit_DCMotor *leftMotorFront = AFMSd.getMotor(1);
Adafruit_DCMotor *leftMotorRear = AFMSd.getMotor(4);

// Encoders
#define RH_ENCODER_A 19
#define RH_ENCODER_B 46
#define LH_ENCODER_A 18
#define LH_ENCODER_B 44

volatile unsigned long leftCount = 0; //Encoder count
volatile unsigned long rightCount = 0;

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

  cnvyr1->setSpeed(150);
  cnvyr1->run(FORWARD);
  cnvyr1->run(RELEASE);
  cnvyr2->setSpeed(150);
  cnvyr2->run(FORWARD);
  cnvyr2->run(RELEASE);

  // Driver Setup
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

  rightMotorFront->run(RELEASE);
  rightMotorRear->run(RELEASE);
  leftMotorFront->run(RELEASE);
  leftMotorRear->run(RELEASE);

  //IMU setup
  Serial.println("Do not destory humanity, not even once, not even as a joke"); Serial.println("");

  if (!bno.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }


  delay(1000);

  bno.setExtCrystalUse(true);


}

void loop() {

  cnvyr1->run(FORWARD);
  cnvyr2->run(BACKWARD);

  cnvyr1->setSpeed(255);
  cnvyr2->setSpeed(255);

  //  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");

    delay(5000);
    forward(30);
    right(90);
    forward(11);
    left(90);
    forward(24);
    left(90);
    forward(26);
    left(90);
    forward(24);
    right(45);
    forward(18);
    right(135);
    forward(46);
    delay(5000);

//  delay(2000);
//  forward(30);


}


void backward(int dist) {
  // Reset the encoder count
  leftCount = 0;
  rightCount = 0;
  unsigned long ticks;

  ticks = dist * 229; //229 ticks per inch

  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(BACKWARD);
  leftMotorRear->run(BACKWARD);
  do {
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  } while (((leftCount + rightCount) / 2) < ticks);

  cleanUp();
}

void forward (int dist) {
  // Reset the encoder count
  leftCount = 0;
  rightCount = 0;
  unsigned long ticks;
  sensors_event_t event;
  float IMUangle;
  
  ticks = dist * 229; //229 ticks per inch

  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);
  do {
//    
//    bno.getEvent(&event);
//    IMUangle = event.orientation.x;
//    if(IMUangle > 1.0 && IMUangle <340 ){
//      left(1);
//        Serial.print("\drift left X: ");
//        Serial.print(event.orientation.x, 0);
//        Serial.println("");
//    } else if(IMUangle < 359 && IMUangle > 300){
//      right(1);
//        Serial.print("\right turn X: ");
//        Serial.print(event.orientation.x, 0);
//        Serial.println("");
//    }
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  } while (((leftCount + rightCount) / 2) < ticks);

  cleanUp();
}
//
void left(float angle) {
  // turning left = higher angle on IMU

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
  while (IMUangle > 360.0 - angle || IMUangle < 2.0) {
    sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x;
    
    if (IMUangle < 360.0 - (angle - (angle * .1))) {
      speed = 80;
      rightMotorFront->setSpeed(speed);
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    } else {
      speed = 150;
      rightMotorFront->setSpeed(speed);
      rightMotorRear->setSpeed(speed);
      leftMotorFront->setSpeed(speed);
      leftMotorRear->setSpeed(speed);
    }
  }
  cleanUp();
  IMUreset();
}


void right(int angle) {
  // Turning right = smaller angle on IMU

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
      speed = 80;
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
  IMUreset();
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
  delay(700);
}

// encoder event for the interrupt call
void leftEncoderEvent() {
  leftCount++;
}

// encoder event for the interrupt call
void rightEncoderEvent() {
  rightCount++;
}
