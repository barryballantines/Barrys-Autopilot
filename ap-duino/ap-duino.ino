
#include "AutoPilot.h"

AutoPilot ap;

void setup() {
  // put your setup code here, to run once:
  ap.setHeading(180);

}

void loop() {
  // put your main code here, to run repeatedly:
  int hdg = ap.getHeading();
  hdg = hdg + 5;
  ap.setHeading(hdg);
  ap.updateDisplay();
  delay(1000);
}
