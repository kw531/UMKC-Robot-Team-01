#include "path.h"
#include "motion.h"

void setup() {
  motionSetup();
}

void loop() {

  runConveyor();
  delay(5000);
  roundOne();
  delay(5000);

}


