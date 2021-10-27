/**
   Snakie McSnakeFace Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   Simple program intended to run on an ATmega328P microcontroller using
        PCD8544 LCD Screen
        3 Push Buttons
        1 8 ohm speaker

   Configure the digital pin connections below
*/

#include "Arduino.h"
#include "Snakie.h"
#include "Button.h"
#include "Lcd.h"
#include "HungerMeter.h"

#ifndef LCD_DIMENSIONS
#define LCD_WIDTH 84
#define LCD_HEIGHT 48
#endif

//Set true if you want verbose outpout on the monitor - note this will dramatically slow the game down
#define DEBUG_MODE false

//LCD Pin Connections
#define LCD_SCLK_PIN 5
#define LCD_SDIN_PIN 6
#define LCD_DC_PIN 7
#define LCD_RES_PIN 8
#define LCD_SCE_PIN 3

//Button Pin Connections
#define LEFT_BUTTON_PIN 9
#define RIGHT_BUTTON_PIN 10
#define START_BUTTON_PIN 12

//Speaker connection
#define SPEAKER_OUT 11

//LED connections
#define RED_HUNGER A1
#define ORANGE1_HUNGER A2
#define ORANGE2_HUNGER A3
#define GREEN_HUNGER A4

//Game class
Snakie* snakie; 

void setup() {
  Serial.begin(9600);

  //Configure hardware
  Lcd *lcd = new Lcd(LCD_SCLK_PIN, LCD_SDIN_PIN, LCD_DC_PIN, LCD_RES_PIN, LCD_SCE_PIN);
  Button *leftButton = new Button(LEFT_BUTTON_PIN, DEBUG_MODE);
  Button *rightButton = new Button(RIGHT_BUTTON_PIN, DEBUG_MODE);
  Button *startButton = new Button(START_BUTTON_PIN, DEBUG_MODE);
  HungerMeter *hunger = new HungerMeter(RED_HUNGER, ORANGE1_HUNGER, ORANGE2_HUNGER, GREEN_HUNGER);

  snakie = new Snakie(lcd, leftButton, rightButton, startButton, SPEAKER_OUT, hunger, DEBUG_MODE);

  
}

void loop() {
  snakie->tick();
}
