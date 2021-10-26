#ifndef Snake_h
#define Snake_h

#include "Arduino.h"

#ifndef LCD_DIMENSIONS
#define LCD_WIDTH 84
#define LCD_HEIGHT 48
#endif

/**
 * Snake directions, set up so a right turn can be:
 *  newdir = (curDir - 1) %r 4
 * and a left turn is 
 *  newdir = (curDir + 1) %r 4
 *  
 * Dont change these!
 */
#define SNAKE_DIR_RIGHT 0
#define SNAKE_DIR_UP 1
#define SNAKE_DIR_LEFT 2
#define SNAKE_DIR_DOWN 3

/** A single snake 'segment' */
class Segment {
  public:
    uint8_t x;
    uint8_t y;
    
    Segment *next = NULL;  //Next segment
    Segment(uint8_t xPos, uint8_t yPos);

    void removeTail();
};

/** 
 *  Main snake class - represents a snake
 */
class Snake {
  public:
    Segment *head;
    uint8_t snakeSize;
    short currentDir;


    //Create a new snake at the given coordinates heading in the given direction
    Snake(uint8_t initialX, uint8_t initialY, uint8_t initialLen, uint8_t initialDir);

    //number of segments
    uint8_t size();

    // Change snake direction counter-clockwise
    void turnLeft();

    // Change snake direction clockwise
    void turnRight();

    // grow the snake 1 unit in the current direction
    // returns true if ok, false if growing would cause a self 'collision'
    boolean grow();

    //remove the last segment
    void removeTail();

    //returns true if some part of the snake is at the given coordinate, otherwise false
    boolean contains(uint8_t x, uint8_t y);

    //Create a string representation of this snake
    String toString();

    //Delete all Segments/Data - free memory - this object can not be used adter this is called
    void destruct(); 
      
};
#endif
