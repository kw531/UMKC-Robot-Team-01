#ifndef PATH_H
#define PATH_H
#include <avr/pgmspace.h>
#include "motionFunctions.h"

//    forward(30);
//    right(90);
//    forward(11);
//    left(90);
//    forward(24);
//    left(90);
//    forward(26);
//    left(90);
//    forward(24);
//    right(45);
//    //start next edge
//    forward(14);
//    right(135);
//    forward(43);
//    right(90);
//    forward(43);
//    right(90);
//    forward(43);
void performMovement(char c, int n);
char round1PickupCode[] = {'f', // travel to box 1
                                                'r', 'f', 'l', 'f', 'l', // box 1
                                                'f', 'l', // travel to box 3
                                                'f', 'r', 'f', 'r', 'f', 'r', 'f', 'r', 'f'}; // box 3
                                                
int round1Pickup[] = {30, // travel to box 1 
                                            90, 11, 90, 24, 90, 26, 90, 24, 45, // box 1
                                            14, 135, // travel to box 3 
                                            43, 90, 43, 90, 43};  // box 3

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
