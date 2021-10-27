/**
   Snakie McSnakeFace - Button Handler (header) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   Used to keep track of button presses - it only counts a press as a transition from LOW to HIGH
   Where it is held HIGH for at least DEBOUNCE_DELAY milliseconds.
*/

#ifndef Button_h
#define Button_h
#include "Arduino.h"
#include "Constants.h"

class Button {
  private:
    bool _debug;
    byte _pin;
    byte _currentState = LOW;
    byte _lastState = LOW;
    long _lastChange = 0;
    byte _pressed = 0;

  public:
    /* Constructor with pin the button is wired to */
    Button(byte pin, bool debug);

    /* Return true if the button has been pressed at least once since last called */
    bool isPressed();

    /* Checks to see if the button is being pressed - should be called as often as possible */
    void check();
};
#endif
