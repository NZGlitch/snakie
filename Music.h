/**
   Snakie McSnakeFace - Music Data (header) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   Stores song definitions in PROGMEM. 
   A song is comprised of a size, melody, and ryhtym section
*/
#ifndef Music_h
#define Music_h

#include "MusicPlayer.h";

const byte pauseSize = 59;
const uint16_t PROGMEM pauseMelody[pauseSize] = { 
  NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_F5,  NOTE_F5,  NOTE_DS5, NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_DS5, NOTE_DS5, NOTE_CS5, NOTE_C5, 
  NOTE_AS4, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_DS5, NOTE_C5,  NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_DS5, NOTE_CS5, NOTE_AS4, 
  NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_F5,  NOTE_F5,  NOTE_DS5, NOTE_AS4, NOTE_AS4, NOTE_GS4, NOTE_GS4, NOTE_GS5, NOTE_C5,  NOTE_CS5, NOTE_C5,  NOTE_AS4, 
  NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_CS5, NOTE_DS5, NOTE_C5,  NOTE_AS4, NOTE_GS4, REST,     NOTE_GS4, NOTE_DS5, NOTE_CS5, REST
};
const uint8_t PROGMEM pauseRhythm[pauseSize] = { 
  1, 1, 1, 1, 3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 1, 3, 3, 3, 1, 2, 2, 2, 4, 8, 1, 
  1, 1, 1, 3, 3, 6,  1, 1, 1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 1, 3, 3, 3, 1, 2, 2, 2, 4, 8, 4
};

Song *pauseSong = new Song(pauseMelody, pauseRhythm, pauseSize);

#endif
