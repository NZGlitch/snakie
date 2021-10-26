/*
  Snakie.h - A library running a game of SnakieMcSnakeFace
*/

#ifndef Snakie_h
#define Snakie_h

#include "Lcd.h"
#include "Button.h"
#include "Snake.h"

// The target tick time in microseconds - the program will try as much as possible to keep
// ticks to this exact length, providing consitency in snake speed during the game
#define TICK_MICROS 1000

#define INITIAL_DIFFICULTY 100   //The initial difficulty in 'ticks per snake move'

//Initial snake size
#define INITIAL_SNAKE_LEN 5

//Current state of the game
#define STATE_LOADING 0
#define STATE_WAITING 1
#define STATE_RUNNING 2
#define STATE_PAUSED 3
#define STATE_ENDGAME 4


class Snakie {
  private:
    bool _debug_mode;         // Sets debug mode
    bool _state_drawn;         //Some states only want to draw once - they can use this to track that
    uint8_t _currentState;    // Current Game State
    uint8_t _appleX;          // Current apple X Coordinate
    uint8_t _appleY;          // Current apple Y Coordinate
    uint8_t _tickCount;       // Tick count since snake last moved
    Lcd *_lcd;                // The screen
    Snake *_snake;            // Our snake
    Button *_left;            // Left Button
    Button *_right;           // Right Button
    Button *_start;           // Start Button

    /* Place the apple somewhere */
    void _placeApple();

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
    Snakie(Lcd *lcd, Button *left, Button *right, Button *start, bool debug_mode);

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
};

#endif
