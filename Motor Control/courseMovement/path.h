#ifndef PATH_H
#define PATH_H
#include "motion.h"
#include "motionFunctions.h"

void performMovement(char c, int n);

// Each round has 2 variables.  round_PickupCode is the type of movement the robot needs to preform.
// This can be forward ('f'), backwards ('b'), left ('l'), right ('r'), still ('s'), dispense ('d')
// round_Pickup is the distance or angle for the robot move.  If it is a distance to move forward or backwards,
// the value is expressed in inches. If it's a turning angle, it's degrees.

char round1PickupCode[] = {'f', // travel to box 1
                           'r', 'f', 'l', 'f', 'l', 'f', 'l', 'f', // box 1
                           'r', 'f', // travel to box 3
                           'r' , 'f', 'r', 'f', 'r', 'f', // box 3
                          'l', 'f'};

int round1Pickup[] = {30, // travel to box 1
                      90, 10, 93, 24, 93, 24, 90, 25, // box 1
                      43, 17, // travel to box 3
                      125, 48, 85, 48, 85, 46 , // box 3
                     45, 24};

char dispenseCode[] = {'d', //red
                        'r','b','d', //green
                        'b','l','d', //blue
                        'b','d',  //gray
                        'b','r','d', // cyan
                        'b','d', //mag
                        'b','r','f','d', //yellow
                        'b'}; //white
int dispenseNum[] = {1, //red
                    45,42,1, //g
                    35,133,1, //b
                    56,1, //gray
                    53,135,1, //cyan
                    40,1, //mag
                    35,90,2,1, //yellow
                    34}; //white

void roundOne() {
  Serial.println(sizeof(round1PickupCode)); Serial.println("");

  for (int i = 0; i <= sizeof(round1PickupCode); i++) {
    //Serial.println(round1PickupCode[0]);
    Serial.println(round1Pickup[0]);
    performMovement(round1PickupCode[i], round1Pickup[i]);
  }
}

void dispense() {
  for (int i = 0; i <= sizeof(dispenseCode); i++) {
    performMovement(dispenseCode[i], dispenseNum[i]);
  }
}

void performMovement(char c, int n) {
  // The case statement which sends the motion and the distance to the motors
  switch (c) {
    case 'f':
      Serial.println("FORWARD");
      forward(n);
      break;
    case 'r':
      Serial.println("RIGHT");
      right(float(n));
      break;
    case 'l':
      Serial.println("LEFT");
      left(float(n));
      break;
    case 'b':
      Serial.println("BACKWARDS");
      backward(n);
      break;
    case 's':
      still(n);
      break;
    case 'd':
      dispense(n);
      break;
    default:
      Serial.println("badnews");
  }
}

#endif





