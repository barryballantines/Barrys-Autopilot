#include "AutoPilot.h"

AutoPilot::AutoPilot() {
    // nothing to do yet...
}

AutoPilot::~AutoPilot() {
    // nothing to destruct yet...
}

void AutoPilot::setHeading(int hdg) {
    _heading = hdg % 360;
}

int AutoPilot::getHeading() {
    return _heading;
}

void AutoPilot::updateDisplay() {
    // nothing in here yet...
}
