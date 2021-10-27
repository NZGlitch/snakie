/**
   Snakie McSnakeFace - HungerMeter (impl) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution
*/
#include "HungerMeter.h"

HungerMeter::HungerMeter(byte red_pin, byte orange1_pin, byte orange2_pin, byte green_pin){

 _red = red_pin;
 _o1 = orange1_pin;
 _o2 = orange2_pin;
 _green = green_pin;
 _currentHunger = MAX_HUNGER;

 pinMode(_red, OUTPUT);
 pinMode(_o1, OUTPUT);
 pinMode(_o2, OUTPUT);
 pinMode(_green, OUTPUT);
}

void HungerMeter::setHunger(uint8_t newHunger){
  if (newHunger > MAX_HUNGER)
    _currentHunger = MAX_HUNGER;
  else
    _currentHunger = newHunger;
}

void HungerMeter::reduceHunger(uint8_t amount) {
  if (_currentHunger < amount)
    _currentHunger = 0;
  else
    _currentHunger = _currentHunger - amount;
}

uint8_t HungerMeter::getHunger() {
  return _currentHunger;
}

void HungerMeter::tick() {
  //calculate our current hunger percentage
  float c = _currentHunger;
  float m = MAX_HUNGER;
  uint8_t pc = (uint8_t) ((c / m) * 100.0);

  if (pc <= 0)
    digitalWrite(_red, LOW);
  else 
    digitalWrite(_red, HIGH);
    
  if (pc < 25)
    digitalWrite(_o1, LOW);
  else
    digitalWrite(_o1, HIGH);

  if (pc < 50)
    digitalWrite(_o2, LOW);
  else
    digitalWrite(_o2, HIGH);

  if (pc < 75)
    digitalWrite(_green, LOW);
  else
    digitalWrite(_green, HIGH);
}
