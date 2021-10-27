/**
   Snakie McSnakeFace - Snakie (header) Version 1.0
   Author: Chris Noldus, Copyright 2021
   Licence: CC w/attribution

   The main game class - handles the operation of the game through various states
*/

#ifndef Snakie_h
#define Snakie_h

#include "Lcd.h"
#include "Button.h"
#include "Snake.h"
#include "Pitches.h"
#include "MusicPlayer.h"
#include "HungerMeter.h"
#include "Constants.h"

//Current state of the game
#define STATE_LOADING 0
#define STATE_WAITING 1
#define STATE_RUNNING 2
#define STATE_PAUSED 3
#define STATE_ENDGAME 4
 
class Snakie {
  private:

    bool _debug_mode;           // Sets debug mode
    bool _state_drawn;          // Some states only want to draw once - they can use this to track that
    uint8_t _currentState;      // Current Game State
    uint8_t _appleX;            // Current apple X Coordinate
    uint8_t _appleY;            // Current apple Y Coordinate
    Lcd *_lcd;                  // The screen
    Snake *_snake;              // Our snake
    Button *_left;              // Left Button
    Button *_right;             // Right Button
    Button *_start;             // Start Button
    byte _speaker;              // Speaker output pin
    MusicPlayer *_musicPlayer;  // For fun!
    uint32_t _score;            // Current Score
    long _lastMove;             // The time elapsed since the snake last moved
    bool _snakeMelHigh = true;  // Whether the next move tone is aa high tone or a low tone
    HungerMeter *_hunger;       // Keep track of hunger
    short _deathReason;         //Actual reason game ended     

    /* Place the apple somewhere */
    void _placeApple();

    /* Returns the 'period' of a a tick for the current difficulty level */
    int _difficultyDelay();

    //Internal state methods

    /* Display the initial screen */
    void _stateLoading();

    /* In this state the start screen should already be displayed, we are just waiting for the player to press start */
    void _stateWaiting();

    /* The main game state where the game is being played */
    void _stateRunning();

    /* The game has been paused */
    void _statePaused();

    /* The game ended */
    void _stateEndgame(); 

  public:
    /* Constructor - requires a screen and some buttons */
    Snakie(Lcd *lcd, Button *left, Button *right, Button *start, byte speaker_out, HungerMeter *hunger, bool debug_mode);

    /* Execute one game tick */
    void tick();

    /* Print the current game state information to Serial */
    void printGameState();

    /* Current x coordinate of apple */
    uint8_t getAppleX();

    /* Current y coordinate of apple */
    uint8_t getAppleY();

    /* Return the current Snake */
    Snake* getSnake();

    void playSound(int melody[], int durations[], int len);
};

#endif
