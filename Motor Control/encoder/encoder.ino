// just reading the encoder, nothing else.

int encoderValue_A = 0;
int encoderValue_B = 0; 

void setup() {

  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  attachInterrupt(digitalPinToInterrupt(2), countA, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), countB, FALLING);
}

void loop() {

      // send the values
      Serial.write(5);
      Serial.write(encoderValue_B);
}


void countA() {

  encoderValue_A++;  
}

void countB() {

  encoderValue_B++;  
}
