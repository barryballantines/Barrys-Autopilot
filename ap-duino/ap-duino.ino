
#include "AutoPilot.h"

AutoPilot ap;

void setup() {
  // put your setup code here, to run once:
  ap.setupShiftRegisterControl(5,6);
  ap.setupHeadingDisplayDataPin(7);
  ap.setupHeadingRotaryEncoder(3,4);
  ap.setHeading(0);

  attachInterrupt(digitalPinToInterrupt(3), interruptRotaryEncoder, RISING);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (false) {
    // testing the heading rotary encoder
    int hdg = ap.getHeading();
    Serial.print("Heading: ");
    Serial.println(hdg);
  }

  // testing the heading display...
  Serial.println("Testing Heading Display");
  ap.testHeadingDisplay();
  delay(3000);
}

void interruptRotaryEncoder() {
  ap.onHeadingRotaryEncoderInterrupt();
}
