/* 
  Plays soe music while the game is paused
*/

#ifndef Pause_h
#define Pause_h

#include "Arduino.h"

#define  a3f    208     // 208 Hz
#define  b3f    233     // 233 Hz
#define  b3     247     // 247 Hz
#define  c4     261     // 261 Hz MIDDLE C
#define  c4s    277     // 277 Hz
#define  e4f    311     // 311 Hz    
#define  f4     349     // 349 Hz 
#define  a4f    415     // 415 Hz  
#define  b4f    466     // 466 Hz 
#define  b4     493     // 493 Hz 
#define  c5     523     // 523 Hz 
#define  c5s    554     // 554 Hz
#define  e5f    622     // 622 Hz  
#define  f5     698     // 698 Hz 
#define  f5s    740     // 740 Hz
#define  a5f    831     // 831 Hz 

#define rest    -1

class Pause {
  private:
    byte _speaker; //pint for audio output
    int _led; //not supported yet
    int _threshold;
    int _index;

    volatile int beatLength = 100;        // determines tempo
    float beatSeparationConstant = 0.3;    

  public:
    Pause(byte pin);
    void step();
};

#endif
