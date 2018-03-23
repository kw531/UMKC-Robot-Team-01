#include "path.h"
#include "motion.h"

int goPin = 37;

void setup() {
  motionSetup();
  pinMode(goPin, INPUT);
}

void loop() {

  if (digitalRead(goPin) == HIGH) {
    //runConveyor();
    delay(2000);
    Serial.print("hi");
    roundOne();
    delay(10000);
  }
}




