/**
   Snakie Mc SnakeFace Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   Simple program intended to run on an ATmega328P microcontroller usinf
        PCD8544 LCD Screen
        3 Push Buttons

   Configure the digital pin connections below
*/

#include "Arduino.h"
#include "Snakie.h"
#include "Button.h"
#include "Lcd.h"

#ifndef LCD_DIMENSIONS
#define LCD_WIDTH 84
#define LCD_HEIGHT 48
#endif

//Set true if you want verbose outpout on the monitor
#define DEBUG_MODE false

//LCD Pin Connections
#define LCD_SCLK_PIN 4
#define LCD_SDIN_PIN 5
#define LCD_DC_PIN 6
#define LCD_RES_PIN 7
#define LCD_SCE_PIN 8

//Button Pin Connections
#define LEFT_BUTTON_PIN 10
#define RIGHT_BUTTON_PIN 11
#define START_BUTTON_PIN 9

Snakie* snakie;   //Game class

void setup() {
  Serial.begin(9600);

  Lcd *lcd = new Lcd(LCD_SCLK_PIN, LCD_SDIN_PIN, LCD_DC_PIN, LCD_RES_PIN, LCD_SCE_PIN);
  Button *leftButton = new Button(LEFT_BUTTON_PIN, DEBUG_MODE);
  Button *rightButton = new Button(RIGHT_BUTTON_PIN, DEBUG_MODE);
  Button *startButton = new Button(START_BUTTON_PIN, DEBUG_MODE);

  snakie = new Snakie(lcd, leftButton, rightButton, startButton, DEBUG_MODE);
}

void loop() {
  snakie->tick();
}
