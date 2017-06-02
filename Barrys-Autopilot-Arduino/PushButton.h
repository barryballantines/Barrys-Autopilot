/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PushButton.h
 * Author: mbuse
 *
 * Created on 2. Juni 2017, 11:13
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H


#include <Arduino.h>

class PushButton {
  
public:
  
  void setup(const byte & pin, const char * name);
  
  const char * getName();
  boolean isPressed();
  boolean isStateChanged();
  
  void readButtonState();
  void clearStateChanged();
  
private:
  
  const char * _name;
  byte _pin;
  
  boolean _statePressed;
  boolean _stateDirty;
  
};


#endif /* PUSHBUTTON_H */

