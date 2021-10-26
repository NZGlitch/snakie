/*
  Button.h - A library for managing button presses in the snake game
*/

#ifndef Button_h
#define Button_h
#include "Arduino.h"

const long DEBOUNCE_DELAY = 50; //Minimum period change has to be stable before it is considered stable

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
