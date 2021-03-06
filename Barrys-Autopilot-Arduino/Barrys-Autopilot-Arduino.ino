
#include "AutoPilot.h"

#define SR_LATCH_PIN 8
#define SR_OUTPUT_ENABLE_PIN 9
#define SR_CLEAR_PIN 10
#define SR_CLOCK_PIN 12

#define HEADING_DISPLAY_SER 11
#define HEADING_CONTROLLER_A_PIN 3
#define HEADING_CONTROLLER_B_PIN 4
#define HEADING_HOLD_LED_PIN 22
#define HEADING_HOLD_BTN_PIN 24
#define HEADING_SELECT_BTN_PIN 26



AutoPilot ap;
int lastHeading = -1;

void setup() {
  // put your setup code here, to run once:
  ap.setupShiftRegisterControl(SR_CLOCK_PIN,SR_LATCH_PIN, SR_CLEAR_PIN, SR_OUTPUT_ENABLE_PIN);
  ap.setupHeadingDisplayDataPin(HEADING_DISPLAY_SER);
  ap.setupHeadingRotaryEncoder(HEADING_CONTROLLER_A_PIN,HEADING_CONTROLLER_B_PIN);
  ap.setupHeadingHoldLED(HEADING_HOLD_LED_PIN);
  ap.setupHeadingHoldBtn(HEADING_HOLD_BTN_PIN);
  ap.setupHeadingSelectBtn(HEADING_SELECT_BTN_PIN);
  ap.setHeading(0);

  attachInterrupt(digitalPinToInterrupt(3), interruptRotaryEncoder, CHANGE);

  Serial.begin(9600);
  while(!Serial) {
    ;
  }
}

void loop() {
  ap.onSerialEvent();
  ap.readButtonStateChanges();
  ap.updateDisplay();
  ap.sendChanges();
  
}

void interruptRotaryEncoder() {
  ap.onHeadingRotaryEncoderInterrupt();
}


