/**
   Snakie McSnakeFace - Music Player (header) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   Defines a 'Song' and a 'Music Player'. The Music player will play songs, each call to step() will play the next note in the song
   NOTE: playing each note will block for the duration of the note
*/

#ifndef MusicPlayer_h
#define MusicPlayer_h

#include "Arduino.h"
#include "Pitches.h"

class Song {
   public:
    const uint16_t *melody;
    const byte *rhythm;
    byte songSize;
    Song(const uint16_t *melody, const byte *rhythm, const byte songSize);
};

class MusicPlayer {
  private:
    byte _speaker; //pint for audio output
    int _threshold;
    uint16_t _index;

    Song *_song;

    const volatile int beatLength = 100;        // determines tempo
    const float beatSeparationConstant = 0.3;    

  public:
    MusicPlayer(byte speakerPin, Song *song);   //Construct with speaker pin rg
    void step();              //Play one note
    void reset();             //Go back to start
};

#endif
