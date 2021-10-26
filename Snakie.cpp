/**
   Snakie McSnakeFace - Snakie (impl) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution
*/
#include "Arduino.h"
#include "Snakie.h"
#include "Music.h"

Snakie::Snakie(Lcd *lcd, Button *left, Button *right, Button *start, byte speaker, bool debug_mode) {
  _lcd = lcd;
  _left = left;
  _right = right;
  _start = start;
  _currentState = STATE_LOADING;
  _debug_mode = debug_mode;
  _speaker = speaker;
}

void Snakie::tick() {
   long tickStart = micros();

   //Check IO
   _left->check();
   _right->check();
   _start->check();
   
  switch (_currentState) {
    case STATE_LOADING: _stateLoading(); break;
    case STATE_WAITING: _stateWaiting(); break;
    case STATE_RUNNING: _stateRunning(); break;
    case STATE_PAUSED:  _statePaused();  break;
    case STATE_ENDGAME: _stateEndgame(); break;
  }
  

  //extend this tick if needed
  long tickTime = (micros() - tickStart);
  long tickDelay = max(0, TICK_MICROS - (tickTime));
  delayMicroseconds(tickDelay);
}

void Snakie::printGameState() {
  Serial.println("NOT IMPLEMENTED");
}

uint8_t Snakie::getAppleX() { return _appleX; }
uint8_t Snakie::getAppleY() { return _appleY; }
Snake* Snakie::getSnake() { return _snake; }

void Snakie::_placeApple() {
  bool applePlaced = false;

  //Keep trying until we put the apple somewhere the snake isn't
  while (!applePlaced) {
    //pick a candidate apple position
    _appleX = random(1, LCD_WIDTH - 2);
    _appleY = random(1, LCD_HEIGHT - 2);
    applePlaced = true;

    if (_debug_mode) {
      Serial.print("Tryng new apple postion ("); Serial.print(_appleX,DEC); Serial.print(","); Serial.print(_appleY); Serial.println(")");
    }

    //check to see if this apple is 'inside' the snake
    if (_snake->contains(_appleX, _appleY)) applePlaced = false;
  }
  if (_debug_mode)
    Serial.println("Apple Position accepted");
}

void Snakie::_stateLoading() {
  if (_debug_mode) Serial.println("STATE: Loading");
  _lcd->printImageFromFlash(loadscreen);
  _currentState =STATE_WAITING;
  
  // Play start-up sound TODO -> use new Song/Music interface
  tone(_speaker,NOTE_E6,125);
  delay(130);
  tone(_speaker,NOTE_G6,125);
  delay(130);
  tone(_speaker,NOTE_E7,125);
  delay(130);
  tone(_speaker,NOTE_C7,125);
  delay(130);
  tone(_speaker,NOTE_D7,125);
  delay(130);
  tone(_speaker,NOTE_G7,125);
  delay(125);
  noTone(_speaker);
}

void Snakie::_stateWaiting() {
  if (_debug_mode) Serial.println("STATE: WAITING");
  //see if start button pressed
  if (_start->isPressed()) {
    
    //Initialise game: clear screen, create new snake and apple.
    
    //TODO - random start & direction
    uint8_t curX = 40;
    uint8_t curY = 24;

    //Create snake
    _snake = new Snake(curX, curY, INITIAL_SNAKE_LEN, SNAKE_DIR_RIGHT);

    if (_debug_mode) {
      Serial.print("Snake CREATED -> "); Serial.println(_snake->toString());
    }
    
    _placeApple();  //place the apple

    if (_debug_mode) Serial.println("STATE: Tranistion to running");
    _currentState = STATE_RUNNING;
    _lastMove = 0;

    //Update display
    _lcd->displayGameState(_snake, _appleX, _appleY);
  }
}

void Snakie::_stateRunning() {
  _state_drawn = false;
  
  //First, handle IO
  
  //If the start button has been pressed, move to the pause state
  if (_start->isPressed()) {
    if (_debug_mode) Serial.println("START Pressed, pausing game");
    _currentState = STATE_PAUSED;
    return;
  }
  
  //If left has been pressed, turn left
  if (_left->isPressed()) {
    if (_debug_mode) Serial.println("LEFT Pressed");
    _snake->turnLeft();
  }
  
  //If right has been pressed, turn right
  if (_right->isPressed()) {
    if (_debug_mode) Serial.println("RIGHT Pressed");
    _snake->turnRight();
  }

  //Check if enough time has passed since we last moved
  long elapsed = millis() - _lastMove;
  if (elapsed > _difficultyDelay()) {
  
    if (_debug_mode) {
      Serial.println("STATE: RUNNING");
    }

    //have we hit ourselves or gone off screen?
    if (!_snake->grow()) {
      if (_debug_mode) Serial.println("OFF SCREEN OR SELF COLLISION!");
      _currentState = STATE_ENDGAME;
    }
    
    //Did we find an apple?
    if (_snake->contains(_appleX, _appleY)) {
      if (_debug_mode) Serial.println("Yummy apple!");
      _placeApple();
      tone(_speaker, NOTE_A7, 50);
      delay(50);
      tone(_speaker, NOTE_B7, 50);
      delay(50);
      tone(_speaker, NOTE_C7, 50);
    } else {
      _snake->removeTail();
        if (_snakeMelHigh) 
      tone(_speaker, NOTE_C4, 10);
    else
      tone(_speaker, NOTE_C5, 10);
    _snakeMelHigh = !_snakeMelHigh;
    }
    
    //Update display
    _lcd->displayGameState(_snake, _appleX, _appleY);
    _lastMove = millis();
  }
}

void Snakie::_statePaused() {
  if (_debug_mode) Serial.println("STATE: PAUSED");
  //Game is paused
  if (!_state_drawn) {
    _lcd->clear();
    _lcd->printString(2, " GAME  PAUSED ");
    _state_drawn = true;
    _musicPlayer = new MusicPlayer(_speaker, pauseSong);
    _musicPlayer->reset();
  }

  _musicPlayer->step();

  //If the start button has been pressed, move to the pause state
  if (_start->isPressed()) {
    if (_debug_mode) Serial.println("START Pressed, pausing game");
    _currentState = STATE_RUNNING;
    delete _musicPlayer;
    _musicPlayer = NULL;
    _state_drawn = false;
    return;
  }
}

//Game has ended
void Snakie::_stateEndgame() {
  if (_debug_mode) Serial.println("STATE: ENDGAME");

  if (!_state_drawn) {
    _lcd->clear();

    const char *message = "score:        ";
    sprintf(message + 7*sizeof(char), "%d",  + _snake->snakeSize);
    _lcd->printString(1, "  GAME  OVER  ");
    _lcd->printString(3, message);
    _state_drawn=true;


    //TODO - use new music class 
    // notes in the melody:
    int gameOverMelody[] = {
      NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
    };
    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int gameOverDurations[] = {
      4, 8, 8, 4, 4, 4, 4, 4
    };
    playSound(gameOverMelody, gameOverDurations,8);

    _snake->destruct();
    delete _snake;
    _snake = NULL;
  }

  //Go back to the home screen
  if (_start->isPressed()) {
    _currentState = STATE_LOADING;
    _state_drawn=false;
    return;
  }
}


int Snakie::_difficultyDelay() {
  //100ms - difficulty, or 0
  if (_snake->snakeSize > 99) return 1;
  return 100 - _snake->snakeSize;
  
}

//TODO Replace with Music class
void Snakie::playSound(int melody[], int durations[], int len) {

for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / durations[thisNote];
    tone(_speaker, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(_speaker);
  }
}
