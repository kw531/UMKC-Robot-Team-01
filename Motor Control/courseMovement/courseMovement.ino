#include "path.h"
#include "motion.h"

void setup() {
  motionSetup();
  pinMode(goPin, INPUT);
  pinMode(modePin, OUTPUT);
  pinMode(dispensePin,OUTPUT);

  digitalWrite(modePin, LOW);
  digitalWrite(dispensePin, LOW);
}

void loop() {

  if (digitalRead(goPin) == HIGH) {
    Serial.print("I made it!");
    //runConveyor();
    //delay(2000);
    //roundOne();
    //delay(5000);
    //stopConveyor();
    digitalWrite(modePin, HIGH); // Tell the Pi to be thinking about dispensing
    dispense();
    delay(1000);
  }
}







