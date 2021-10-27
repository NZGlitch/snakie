/**
   Snakie McSnakeFace - Lcd Driver (header) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   Simple display driver for PCD8544 display (NOKIA Screen)
*/

#ifndef Lcd_h
#define Lcd_h

#include "Arduino.h"
#include "Snake.h"
#include "Glyphs.h"
#include "Constants.h"

const uint8_t PCD8544_CMD = LOW;
const uint8_t PCD8544_DATA = HIGH;

class Lcd {
  private:
    //pins
    uint8_t _SCLK;
    uint8_t _SDIN;
    uint8_t _DC;
    uint8_t _RES;
    uint8_t _SCE;

    //Send a message to the hardware
    void send(uint8_t type, uint8_t data);

    //Set the current cursor position in the harware
    void setCursor(uint8_t column, uint8_t line);
  
  public:
    /* Constructor */
    Lcd(byte sclk, byte sdin, byte dc, byte res, byte sce);

    /* Clears the screen and reset cursor to 0,0 */
    void clear();

    /* Displays an image from FLASH Memory 9i.e. PROGMEM */
    void printImageFromFlash(const uint8_t *image);

    /* Displays an image from SRAM */
    void printImageFromRam(const uint8_t *image);

    /* Prints the given text on the specified line - note only 14 characters will fit on a line. 
     * This method will automatically move to the next line and even wrap around to the top if more are given
     */
    void printString(uint8_t line, const char *string);

    /* Changes the state of a specific pixel */
    void toggleImageBit(uint8_t *image, uint16_t x, uint16_t y, bool on);

    /* Displays the current game state */
    void displayGameState(Snake *snake, uint8_t appleX, uint8_t appleY);
};

#endif
