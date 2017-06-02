/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "PushButton.h"
#include "Arduino.h"

void PushButton::setup(const byte & pin, const char * name) {
  _name = name;
  _pin = pin;
  pinMode(_pin, INPUT_PULLUP);
}

void PushButton::readButtonState() {
  byte state = digitalRead(_pin);
  if (!_statePressed && state==LOW) {
    // BTN pressed
    _statePressed = true;
    _stateDirty = true;
  }
  else if (_statePressed && state==HIGH) {
    // BTN released
    _statePressed = false;
    _stateDirty = false;
  }
}

const char * PushButton::getName() {
  return _name;
}

boolean PushButton::isPressed() {
  return _statePressed;
}

boolean PushButton::isStateChanged() {
  return _stateDirty;
}

void PushButton::clearStateChanged() {
  _stateDirty = false;
}
