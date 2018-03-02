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
  Serial.println("Jolene, Jolene, Jolene, Jolene. Oh I begging of you please don't steal my man..."); Serial.println("");

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
  forward(31);
  right(90);
  forward(12);
  left(90);
  forward(24);
  left(90);
  forward(28);
  left(90);
  forward(24);
  delay(5000);

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

  ticks = dist * 229; //229 ticks per inch

  rightMotorFront->run(FORWARD);
  rightMotorRear->run(FORWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);
  do {
    rightMotorFront->setSpeed(150);
    rightMotorRear->setSpeed(150);
    leftMotorFront->setSpeed(150);
    leftMotorRear->setSpeed(150);
  } while (((leftCount + rightCount) / 2) < ticks);

  cleanUp();
}
//
void left(int angle) {
  // turning left = higher angle on IMU
  IMUreset();
  int IMUangle = 0;
  int speed;
  rightMotorFront->run(BACKWARD);
  rightMotorRear->run(BACKWARD);
  leftMotorFront->run(FORWARD);
  leftMotorRear->run(FORWARD);

  sensors_event_t event;
  bno.getEvent(&event);
  IMUangle = event.orientation.x;

  Serial.print("\tLeft turn X: ");
  Serial.print(event.orientation.x, 0);
  Serial.println("");
  while (IMUangle > 360 - (angle - 3) || IMUangle < 2) {
    sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x;

    speed = 150;

    rightMotorFront->setSpeed(speed);
    rightMotorRear->setSpeed(speed);
    leftMotorFront->setSpeed(speed);
    leftMotorRear->setSpeed(speed);


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

  while (IMUangle < (angle - 1) || IMUangle >= 359) {
    sensors_event_t event;
    bno.getEvent(&event);
    IMUangle = event.orientation.x;

    speed = 150;

    rightMotorFront->setSpeed(speed);
    rightMotorRear->setSpeed(speed);
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

void IMUreset() {
  // Resets the IMU so that the calibration is zero after a turn
  bno.begin();
  delay(800);
}

// encoder event for the interrupt call
void leftEncoderEvent() {
  leftCount++;
}

// encoder event for the interrupt call
void rightEncoderEvent() {
  rightCount++;
}
