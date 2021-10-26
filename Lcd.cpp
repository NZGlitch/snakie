/**
   Snakie McSnakeFace - Lcd Driver (impl) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution
*/

#include "Lcd.h"

void Lcd::send(uint8_t type, uint8_t data) {
  digitalWrite(_DC, type);
  digitalWrite(_SCE, LOW);
  shiftOut(_SDIN, _SCLK, MSBFIRST, data);
  digitalWrite(_SCE, HIGH);
}

void Lcd::setCursor(uint8_t column, uint8_t line) {
  column = (column % LCD_WIDTH);
  line = (line % (LCD_HEIGHT / 9 + 1));
  send(PCD8544_CMD, 0x80 | column);
  send(PCD8544_CMD, 0x40 | line);
}

Lcd::Lcd(byte sclk, byte sdin, byte dc, byte res, byte sce) {
  //Configure pins
  _SCLK = sclk;
  _SDIN = sdin;
  _DC = dc;
  _RES = res;
  _SCE = sce;

  pinMode(_SCLK, OUTPUT);
  pinMode(_SDIN, OUTPUT);
  pinMode(_DC, OUTPUT);
  pinMode(_RES, OUTPUT);
  pinMode(_SCE, OUTPUT);

  // Reset the controller state...
  digitalWrite(_RES, HIGH);
  digitalWrite(_SCE, HIGH);
  digitalWrite(_RES, LOW);
  delay(100);
  digitalWrite(_RES, HIGH);

  // Set LCD Params
  send(PCD8544_CMD, 0x21);  // extended instruction set control (H=1)
  send(PCD8544_CMD, 0x13);  // bias system (1:48)
  send(PCD8544_CMD, 0xc2);  // default Vop (3.06 + 66 * 0.06 = 7V)
  send(PCD8544_CMD, 0x20);  // extended instruction set control (H=0)
  send(PCD8544_CMD, 0x09);  // all display segments on  
  clear();

  //Activate LCD...
  send(PCD8544_CMD, 0x08);  // display blank
  send(PCD8544_CMD, 0x0c);  // normal mode (0x0d = inverse mode)
  delay(100);

  // Place the cursor at the origin...
  send(PCD8544_CMD, 0x80);
  send(PCD8544_CMD, 0x40);
}

void Lcd::clear() {
  setCursor(0, 0);
    for (uint16_t i = 0; i < LCD_WIDTH * (LCD_HEIGHT / 8); i++) {
      send(PCD8544_DATA, 0x00);
    }
  setCursor(0, 0);
}

void Lcd::printImageFromFlash(const uint8_t *image) {
  uint16_t index = 0;
  setCursor(0, 0);
  for (uint8_t line = 0; line < 6; line++) {
    for (uint8_t x = 0; x < LCD_WIDTH; x++) {
      uint8_t val = pgm_read_word_near(image + index++);
      send(PCD8544_DATA, val);
    }
  }
}


void Lcd::printImageFromRam(const uint8_t *image) {
  uint16_t index = 0;
  setCursor(0, 0);
  for (uint8_t line = 0; line < 6; line++) {
    for (uint8_t x = 0; x < LCD_WIDTH; x++) {
      uint8_t val = image[index++];
      send(PCD8544_DATA, val);
    }
  }
}

void Lcd::toggleImageBit(uint8_t *image, uint16_t x, uint16_t y, bool on) {
 //Convert an 'x,y' to a byte address
 uint16_t lineIndex = ((y/8)*LCD_WIDTH)+x;
 //identify which 'bit' in the line is going to change
 uint8_t lineBit = y % 8;

 if (on) //turn bit on - we do this by orring the current image byte with a '1' at the right bit postion
  image[lineIndex] = image[lineIndex] | (0x01 << lineBit);
 else //turn bit off - we do this by anding the current image with a byte that has a 0 at the right position
  image[lineIndex] = image[lineIndex] & (~(0x01 << lineBit));
}


void Lcd::displayGameState(Snake *snake, uint8_t appleX, uint8_t appleY) {
  //load the base screen
 uint8_t screen[504];
 for (int i = 0; i< 504; i++) {
  screen[i] = pgm_read_byte_near(border + i);
 }

 //turn on 'apple' pixel
 toggleImageBit(screen, appleX, appleY, true);

 // Render the snake - for each segment, turn on segment 'pixel'
 Segment *seg = snake->head;
 while(seg != NULL) {
  toggleImageBit(screen, seg->x, seg->y, true);
  seg = seg->next;
 }

 //display
 printImageFromRam(screen);
  
}

void Lcd::printString(uint8_t line, const char* string) {
  setCursor(0, line);
  uint8_t charIndex = 0;
  char ch = string[charIndex++];
  while (ch != '\0') {
    for (int i=0; i<5; i++) {
      uint8_t val = pgm_read_byte_near(FONT_TABLE[ch - 0x20] + i);
      send(PCD8544_DATA, val);
    }
    send(PCD8544_DATA, 0x00);
    ch = string[charIndex++];
  }
}
