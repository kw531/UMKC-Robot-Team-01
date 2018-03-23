#ifndef PATH_H
#define PATH_H
#include <avr/pgmspace.h>
#include "motionFunctions.h"

void performMovement(char c, int n);
char round1PickupCode[] = {'f', // travel to box 1
                                                'r', 'f', 'l', 'f', 'l', 'f', 'l', 'f', // box 1
                                                'r', 'f', // travel to box 3
                                                'r' ,'f', 'r', 'f', 'r', 'f', 'l', 'f','r','f'}; // box 3
                                                
int round1Pickup[] = {30, // travel to box 1 
                                            90, 11, 90, 24, 93, 24, 90, 25, // box 1
                                            45, 17, // travel to box 3 
                                            127, 48, 85, 48, 85, 46 ,45, 25, 135, 45};  // box 3

void roundOne() {
  Serial.println(sizeof(round1PickupCode)); Serial.println("");
  
  for (int i = 0; i <= sizeof(round1PickupCode); i++) {
    //Serial.println(round1PickupCode[0]);
    Serial.println(round1Pickup[0]);
    performMovement(round1PickupCode[i], round1Pickup[i]);
  }
}

void performMovement(char c, int n) {
    //Serial.println(c);
    Serial.println(n);
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

