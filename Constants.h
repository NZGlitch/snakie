#ifndef Constants_cpp
#define Constants_cpp

#define DEATH_ALIVE 0
#define DEATH_WALL 1
#define DEATH_SELF 2
#define DEATH_HUNGER 3

#define LCD_WIDTH 84
#define LCD_HEIGHT 48

//Minimum period change has to be stable before it is considered stable
//I have found that debouncing has too big an impact on responsiveness, so set to 0
#define DEBOUNCE_DELAY 0 

//Defines what 100% on the hunger bar is.
#define MAX_HUNGER LCD_WIDTH+LCD_HEIGHT

// The target tick time in microseconds - the program will try as much as possible to keep
// ticks to this exact length, providing consitency in snake speed during the game
// NOTE - it looks like the current tick length is 25ms-80ms, this is due to blocking sound effects
// TODO find a way to make sound without blocking to speed up ticks
#define TICK_MICROS 1000

//Initial snake size
#define INITIAL_SNAKE_LEN 5

namespace constants {
  //Causes of death - I had try to do this as an 2D char array but it created inexplicable wierd bugs :/
  const char deathTextAlive[] = "Alive!";
  const char deathTextWall[] = "Hit Wall!";
  const char deathTextSelf[] = "Hit Self!";
  const char deathTextHunger[] = "Starved!";  
}

#endif
