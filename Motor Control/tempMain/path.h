#ifndef PATH_H
#define PATH_H
#include "motionFunctions.h"

void performMovement(char c, int n);

// Each round has 2 variables.  round_PickupCode is the type of movement the robot needs to preform. 
// This can be forward ('f'), backwards ('b'), left ('l'), and right ('r')
// round_Pickup is the distance or angle for the robot move.  If it is a distance to move forward or backwards,
// the value is expressed in inches. If it's a turning angle, it's degrees.

char round1PickupCode[] = {'f', // travel to box 1
                           'r', 'f', 'l', 'f', 'l', 'f', 'l', 'f', // box 1
                           'r', 'f', // travel to box 3
                           'r' ,'f', 'r', 'f', 'r', 'f', // box 3
                           'l', 'f','r','f'}; // Travel to red square then to white square
                                                
int round1Pickup[] = {30, // travel to box 1 
                      90, 9, 92, 25, 93, 24, 90, 25, // box 1
                      45, 17, // travel to box 3 
                      127, 48, 85, 48, 85, 46 , // box 3
                      45, 24, 135, 40};  // Travel to red square then to white square

void roundOne() {
  Serial.println(sizeof(round1PickupCode)); Serial.println("");
  
  for (int i = 0; i <= sizeof(round1PickupCode); i++) {
    //Serial.println(round1PickupCode[0]);
    Serial.println(round1Pickup[0]);
    performMovement(round1PickupCode[i], round1Pickup[i]);
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
      right(n);
      break;
    case 'l':
      Serial.println("LEFT");
      left(n);
      break;
    case 'b':
      Serial.println("BACKWARDS");
      backward(n);
      break;
     default:
      Serial.println("badnews");
  }
}

#endif


