#ifndef MOTION_H
#define MOTION_H

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

// All motion
void motionSetup();

// Conveyors
void conveyorSetup();
void runConveyor();
void stopConveyor();

// Drivers
void driversSetup();
void moveRobot(int dist);
void forward (int dist);
void backward (int dist);
void left(float angle);
void right(int angle);
void still(int sec);
void cleanUp();

// IMU
void IMUSetup();
void IMUreset();

// encoder
void encoderSetup();
void leftEncoderEvent();
void rightEncoderEvent();
void setupMotion();

#endif





