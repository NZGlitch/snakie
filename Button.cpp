/**
   Snakie McSnakeFace - Button Handler (impl) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution
*/

#include "Arduino.h"
#include "Button.h"

Button::Button(byte pin, bool debug) {
  _pin = pin;
  _debug = debug;
  pinMode(_pin, INPUT);
}

bool Button::isPressed() {
  if (_pressed > 0) {
    _pressed = 0;
    return true;
  }
  return false;
}

void Button::check() {
  byte readState = digitalRead(_pin);

  //The button has changed state
  if (readState != _lastState) {
    if (_debug) {
      Serial.print(F("BUTTON ")); Serial.print(_pin);
      Serial.print(F(" READSTATE (")); Serial.print(readState);
      Serial.print(F(") != LAST (")); Serial.print(_lastState); Serial.println(F(")"));
    }

    _lastState = readState;
    _lastChange = millis();

    //We changed recently, but have not 'latched'
  } else if (_lastState != _currentState) {
    //See if enough time has passed without noise
    if (millis() - _lastChange > DEBOUNCE_DELAY) {
      _currentState = _lastState;
      if (_currentState == HIGH) _pressed = _pressed + 1;    //increment change count
      if (_debug) {
        Serial.print(F("BUTTON ")); Serial.print(_pin);
        Serial.print(F(" CHANGE TO ")); Serial.print(_currentState);
        Serial.print(F(" PRESSED ")); Serial.println(_pressed);
      }
    }
  }
}
