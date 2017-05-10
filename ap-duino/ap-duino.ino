
#include "AutoPilot.h"

AutoPilot ap;

void setup() {
  // put your setup code here, to run once:
  ap.setupHeadingRotaryEncoder(3,4);
  ap.setHeading(0);

  attachInterrupt(digitalPinToInterrupt(3), interruptRotaryEncoder, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int hdg = ap.getHeading();
  Serial.print("Heading: ");
  Serial.println(hdg);
  delay(1000);
}

void interruptRotaryEncoder() {
  ap.onHeadingRotaryEncoderInterrupt();
}
