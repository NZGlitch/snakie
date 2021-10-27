/**
   Snakie McSnakeFace - HungerMeter (impl) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution
*/
#include "HungerMeter.h"

HungerMeter::HungerMeter(byte red_pin, byte orange1_pin, byte orange2_pin, byte green_pin) {

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

void HungerMeter::setHunger(uint8_t newHunger) {
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

  //First work out which stage we are up to
  byte stage = 0;
  byte blinkLevel = 0;


  if (_currentHunger > 0 && pc < 30) {
    stage = 1;
    blinkLevel = pc - 5;
  }  else if (pc >= 25 && pc < 50) {
    stage = 2;
    blinkLevel = pc - 30;
  } else if (pc >= 50 && pc < 75) {
    stage = 3;
    blinkLevel = pc - 50;
  } else {
    stage = 4;
    blinkLevel = pc - 75;
  }


  switch (stage) {
    case 0: writeLights(LOW, LOW, LOW, LOW); break;
    case 1: writeLights(HIGH, LOW, LOW, LOW); blink(_red, blinkLevel); break;
    case 2: writeLights(HIGH, HIGH, LOW, LOW); blink(_o1, blinkLevel); break;
    case 3: writeLights(HIGH, HIGH, HIGH, LOW); blink(_o2, blinkLevel); break;
    case 4: writeLights(HIGH, HIGH, HIGH, HIGH); blink(_green, blinkLevel); break;
  }
}

void HungerMeter::writeLights(byte red, byte o1, byte o2, byte grn) {
  digitalWrite(_red, red);
  digitalWrite(_o1, o1);
  digitalWrite(_o2, o2);
  digitalWrite(_green, grn);
}

void HungerMeter::blink(byte pin, byte blinkLevel) {
  //Serial.println(blinkLevel, DEC);
  //nothing to do here
  if (blinkLevel > 5) {
    _lastBlinkChange = millis;
    _blinkState = true;
    return;
  }

  int blinkRate =  100;
  int elapsed = millis() - _lastBlinkChange;
  //Serial.print("e:"); Serial.print(elapsed, DEC); Serial.print(" r:"); Serial.println(blinkRate, DEC);
  if (elapsed > blinkRate) {
    _blinkState = !_blinkState;
    _lastBlinkChange = millis();
  }
  digitalWrite(pin, _blinkState);

}
