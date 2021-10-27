/**
   Snakie McSnakeFace - HungerMeter (header) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   This class handles the hunger meter - as the snake moves, he gets hungry
   If he is not fed fast enough he will die of starvation

   The hunger meter is made up of 5 LED's - a red one, 2 orange, and a green.

   LED's will blnk breifly before going out. the rate of blinking speeds up as it gets closer to being extinguished

   Green SOLID >= 80%, Blinking >= 75% < 80%
   Orange2 SOLID >= 55%, Blinking >= 50% < 55%
   Orange1 SOLID >= 30%, Blinking >= 25% < 30%
   Red SOLID >= 5%, Blinking > 0 < 5%
*/

#ifndef HungerMeter_h
#define HungerMeter_h

#include "Arduino.h"

#define MAX_HUNGER 150

class HungerMeter {
  private:
    //Pins
    byte _red;
    byte _o1;
    byte _o2;
    byte _green;

    uint8_t _currentHunger;

  public:
    //Constructor - sets the size of the HungerMeter, and pins
    HungerMeter(byte red_pin, byte orange1_pin, byte orange2_pin, byte green_pin);

    //Set the current hunger level
    void setHunger(uint8_t newHunger);

    //Reduce the HungerMeter by the given amount - will not go below 0
    void reduceHunger(uint8_t amount);

    //Return the current hunger level
    uint8_t getHunger();

    //Update LED states - should be called as often as possible
    void tick();
    
};

#endif
