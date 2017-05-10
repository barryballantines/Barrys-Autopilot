#include "AutoPilot.h"

AutoPilot::AutoPilot() {
    // nothing to do yet...
}

AutoPilot::~AutoPilot() {
    // nothing to destruct yet...
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
