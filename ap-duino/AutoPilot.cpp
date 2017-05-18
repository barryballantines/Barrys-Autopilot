#include "AutoPilot.h"

#define SR_BYTE_BUFFER_SIZE 5

#define SPACE 10
#define MINUS 11
#define DOT   12

byte headingBytes[SR_BYTE_BUFFER_SIZE];

AutoPilot::AutoPilot() {
    // nothing to do yet...
    _commandInput.reserve(200);
}

AutoPilot::~AutoPilot() {
    // nothing to destruct yet...
}

void AutoPilot::setupShiftRegisterControl(byte clockPin, byte latchPin, byte clearPin, byte outputEnablePin) {
  _shiftRegClockPin = clockPin;
  _shiftRegLatchPin = latchPin;
  _shiftRegClearPin = clearPin;
  _shiftRegOutputEnablePin = outputEnablePin;

  pinMode(_shiftRegClockPin, OUTPUT);
  pinMode(_shiftRegLatchPin, OUTPUT);
  pinMode(_shiftRegClearPin, OUTPUT);
  pinMode(_shiftRegOutputEnablePin, OUTPUT);
  digitalWrite(_shiftRegClockPin, LOW);
  digitalWrite(_shiftRegLatchPin, LOW);
  digitalWrite(_shiftRegClearPin, LOW);
  digitalWrite(_shiftRegClearPin, HIGH);
  digitalWrite(_shiftRegOutputEnablePin, LOW);
}

// === HEADING ===

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

void AutoPilot::setupHeadingModeActivateBtn(byte hdgModeActivatePin) {
  _headingModeActivatePin = hdgModeActivatePin;
  pinMode(_headingModeActivatePin, INPUT_PULLUP);
}

void AutoPilot::setupHeadingHoldBtn(byte hdgHoldBtnPin) {
  _headingHoldBtnPin = hdgHoldBtnPin;
  pinMode(_headingHoldBtnPin, INPUT_PULLUP);
    
}

void AutoPilot::setupHeadingModeLED(byte hdgModeLEDPin) {
  _headingModeLEDPin = hdgModeLEDPin;
  pinMode(_headingModeLEDPin, OUTPUT);
  digitalWrite(_headingModeLEDPin, LOW);
}

void AutoPilot::setHeading(int hdg) {
    _heading = (hdg+360) % 360;
    _headingDirty = true;
}

int AutoPilot::getHeading() {
    return _heading;
}

void AutoPilot::updateDisplay() {
    // === STORAGE REGISTER LOW ===
    digitalWrite(_shiftRegLatchPin, LOW);
   
    // === HEADING ===
  
    translateUnsignedIntToByteArray(_heading, headingBytes);
    for (int i; i<SR_BYTE_BUFFER_SIZE; i++) {
      shiftOut(_headingDisplayDataPin, _shiftRegClockPin, LSBFIRST, headingBytes[i]);
    }
    
    // === STORAGE REGISTER HIGH ===
    digitalWrite(_shiftRegLatchPin, HIGH);
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


void AutoPilot::testHeadingDisplay() {
  for (int i=0; i<13; i++) {
    digitalWrite(_shiftRegLatchPin, LOW);
    byte segments = DIGIT_TO_BYTES[i];
    shiftOut(_headingDisplayDataPin, _shiftRegClockPin, LSBFIRST, segments);
    digitalWrite(_shiftRegLatchPin, HIGH);
    delay(1000);
  }
}

// === SERIAL COMM ===

void AutoPilot::sendChanges() {
  if (_headingDirty) {
    Serial.print("[hdg:");
    Serial.print(_heading);
    Serial.println("}");
    _headingDirty = false;
  }
}

void AutoPilot::onSerialEvent() {

  while (Serial.available()) {
    char in = (char) Serial.read();
    if (in == '{') {
      _commandInput = "";
    }
    else if (in == '}') {
      executeCommand();
    }
    else {
      _commandInput += in;
    }
  }
}

void AutoPilot::executeCommand() {
  if (_commandInput.startsWith("hdg:")) {
    int value = (int) _commandInput.substring(4).toInt();
    setHeading(value);
  }
}

// === Utility Methods ===

byte digitToByte(int digit) {
  if (digit>=0 && digit<13) {
    return DIGIT_TO_BYTES[digit];
  } else {
    return B00000000;
  }
}

void translateUnsignedIntToByteArray(unsigned int input, byte output[SR_BYTE_BUFFER_SIZE]) {
  if (input > 99999) {
    for (int i=0; i<SR_BYTE_BUFFER_SIZE; i++) {
      output[i] = B00000010;
    }
  }
  else {
    unsigned int modulo = 10000;
    unsigned int value = input;
    for (int i=0; i<SR_BYTE_BUFFER_SIZE; i++) {
      int digit = value / modulo;
      output[i] = digitToByte(digit);
      value = value - digit * modulo;
      modulo = modulo / 10;
    }
  }
}

