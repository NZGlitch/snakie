/**
   Snakie McSnakeFace - Music Player (impl) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution
*/
#include "MusicPlayer.h"

Song::Song(const uint16_t *melody, const byte *rhythm, const byte songSize) {
  this->melody = melody;
  this->rhythm = rhythm;
  this->songSize = songSize;  
}

MusicPlayer::MusicPlayer(byte speakerPin, Song *song) {
  _speaker = speakerPin;
  _index = 0;
  _song = song;
  pinMode(_speaker, OUTPUT);
}

void MusicPlayer::step() {
  uint16_t note = pgm_read_word(_song->melody + _index );
  byte rhythm = pgm_read_byte(_song->rhythm + _index);    
  uint16_t noteLength = beatLength * rhythm;
  
  if (note > 0) {
    tone(_speaker, note, noteLength);
  }
  
  _index++;
  
  if (_index >= _song->songSize) {
    _index = 0;
  }
  
  delay(noteLength);
  noTone(_speaker);
  delay(noteLength * beatSeparationConstant);
}

void MusicPlayer::reset() {
  _index = 0;
}
