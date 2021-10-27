#ifndef Constants_cpp
#define Constants_cpp

#define DEATH_ALIVE 0
#define DEATH_WALL 1
#define DEATH_SELF 2
#define DEATH_HUNGER 3

#define LCD_WIDTH 84
#define LCD_HEIGHT 48

//Minimum period change has to be stable before it is considered stable
//I ave found that debouncing has to big an impact on responsiveness, so set to 0
#define DEBOUNCE_DELAY 0 

//Defines what 100% on the hunger bar is.
#define MAX_HUNGER LCD_WIDTH+LCD_HEIGHT

namespace constants {
    //Causes of death - TODO use String class and store in an array
    const char deathTextAlive[] = "Alive!";
    const char deathTextWall[] = "Hit Wall!";
    const char deathTextSelf[] = "Hit Self!";
    const char deathTextHunger[] = "Starved!";
   
   
}

#endif
