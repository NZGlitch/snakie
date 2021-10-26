#include "Pause.h"

const int melody[] = { b4f, b4f, a4f, a4f, f5, f5, e5f, b4f, b4f, a4f, a4f, e5f, e5f, c5s, c5, 
  b4f, c5s, c5s, c5s, c5s, c5s, e5f, c5, b4f, a4f, a4f, a4f, e5f, c5s, b4f, b4f, a4f, a4f, f5, f5, e5f, b4f, 
  b4f, a4f, a4f, a5f, c5, c5s, c5, b4f, c5s, c5s, c5s, c5s, c5s, e5f, c5, b4f, a4f, rest, a4f, e5f, c5s, rest
};

const byte rhythmn[] = { 
  1, 1, 1, 1, 3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 1, 3, 3, 3, 1, 2, 2, 2, 4, 8, 1, 1, 1, 1, 3, 3, 6, 
  1, 1, 1, 1, 3, 3, 3, 1, 2, 1, 1, 1, 1, 3, 3, 3, 1, 2, 2, 2, 4, 8, 4
};

Pause::Pause(byte pin) {
  _speaker = pin;
  pinMode(_speaker, OUTPUT);
  _index = 0;
}

void Pause::step() {
  int noteLength;
  
  noteLength = beatLength * rhythmn[_index];
  if (melody[_index] > 0) {
    tone(_speaker, melody[_index], noteLength);
  }
  
  _index++;
  
  if (_index >= sizeof(melody) / sizeof(int)) {
    _index = 0;
  }
  
  delay(noteLength);
  noTone(_speaker);
  delay(noteLength * beatSeparationConstant);
}
