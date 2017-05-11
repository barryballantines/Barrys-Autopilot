#include "AutoPilot.h"

#define SPACE 10
#define MINUS 11
#define DOT   12

AutoPilot::AutoPilot() {
    // nothing to do yet...
}

AutoPilot::~AutoPilot() {
    // nothing to destruct yet...
}

void AutoPilot::setupShiftRegisterControl(byte clockPin, byte latchPin) {
  _clockPin = clockPin;
  _latchPin = latchPin;

  pinMode(_clockPin, OUTPUT);
  digitalWrite(_clockPin, LOW);

  pinMode(_latchPin, OUTPUT);
  digitalWrite(_latchPin, LOW);
}

void AutoPilot::setupHeadingDisplayDataPin(byte dataPin) {
  _headingDisplayDataPin = dataPin;
  pinMode(_headingDisplayDataPin, OUTPUT);
  digitalWrite(_headingDisplayDataPin, LOW);
}

void AutoPilot::setupHeadingRotaryEncoder(byte pinA, byte pinB) {
    _headingEncoderPinA = pinA;
    _headingEncoderPinB = pinB;
    pinMode(_headingEncoderPinA, INPUT_PULLUP);
    pinMode(_headingEncoderPinB, INPUT_PULLUP);
}

void AutoPilot::setHeading(int hdg) {
    _heading = (hdg+360) % 360;
}

int AutoPilot::getHeading() {
    return _heading;
}

void AutoPilot::updateDisplay() {
    // nothing in here yet...
}


void AutoPilot::onHeadingRotaryEncoderInterrupt() {
    int valA = digitalRead(_headingEncoderPinA);
    int valB = digitalRead(_headingEncoderPinB);
    if (valA == valB) {
        setHeading(_heading - 1);
    }
    else {
        setHeading(_heading + 1);
    }
}

// segment byte order: a b c d e f g DP
const byte DIGIT_TO_BYTES[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B00000000, // SPACE
  B00000010, // -
  B00000001, // .
};

byte digitToByte(int digit) {
  if (digit>=0 && digit<13) {
    return DIGIT_TO_BYTES[digit];
  } else {
    return B00000000;
  }
}


void AutoPilot::testHeadingDisplay() {
  for (int i=0; i<13; i++) {
    Serial.print("Testing ");
    Serial.print(i);
    Serial.println(".");
    byte segments = DIGIT_TO_BYTES[i];
    shiftOut(_headingDisplayDataPin, _clockPin, LSBFIRST, segments);
    //digitalWrite(_latchPin, HIGH);
    //digitalWrite(_latchPin, LOW);
    delay(1000);
  }
}


