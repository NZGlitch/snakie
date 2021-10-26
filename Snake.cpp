#include "Snake.h"

Segment::Segment(uint8_t xPos, uint8_t yPos) {
  x = xPos;
  y = yPos;
}

    
void Segment::removeTail() {
  if (next->next == NULL) {
    delete next;
    next = NULL;
  } else {
    next->removeTail();
  }
}

//Create a new snake at the given coordinates heading in the given direction
Snake::Snake(uint8_t initialX, uint8_t initialY, uint8_t initialLen, uint8_t initialDir) {
  head = new Segment(initialX, initialY);
  snakeSize = 1;
  currentDir = initialDir;

  //If we are left or right, then dx: LEFT = 0 - 1 = -1, RIGHT = 2 - 1 = 1
  uint8_t dx = initialDir % 2 == 0 ? initialDir - 1 : 0; 
  //If we are up or down, then dy: UP = 1 - 2 = -1, DOWN = 3 - 2 = 1
  uint8_t dy = initialDir % 2 == 1 ? initialDir - 2 : 0;

  //create the rest of the snake
  Segment *curNode = head;
  while(snakeSize < initialLen) {
    curNode->next = new Segment(curNode->x - dx, curNode->y - dy);
    curNode = curNode->next;
    snakeSize++;
  }
}

uint8_t Snake::size() {
  return snakeSize;
}

void Snake::turnLeft() {
  currentDir = currentDir + 4;  //avoid having to deal with negative numbers
  currentDir = (currentDir - 1) % 4;
}

void Snake::turnRight() {
  currentDir = (currentDir + 1) % 4;
}

boolean Snake::grow() {
  //If we are left or right, then dx: LEFT = 0 - 1 = -1, RIGHT = 2 - 1 = 1
  uint8_t newX = head->x + (currentDir % 2 == 0 ? currentDir - 1 : 0); 
  //If we are up or down, then dy: UP = 1 - 2 = -1, DOWN = 3 - 2 = 1
  uint8_t newY = head->y + (currentDir % 2 == 1 ? currentDir - 2 : 0);

  //check to see if we go out of bounds
  if (newX == 0 || newY == 0 || newX == (LCD_WIDTH - 1) || newY == (LCD_HEIGHT - 1)) return false;

  //check to see if it collides with any other part of the snake
  Segment *cur = head;
  while (cur != NULL) {
    if (cur->x == newX && cur->y == newY) return false;
    cur = cur->next;
  }

  //create new head and add to front
  Segment *newHead = new Segment(newX, newY);
  newHead->next = head;
  head = newHead;

  snakeSize++;

  return true;
}

void Snake::removeTail() {
  head->removeTail();
  snakeSize--;
}

//returns true if some part of the snake is at the given coordinate, otherwise false
boolean Snake::contains(uint8_t x, uint8_t y) {
  Segment *cur = head;
  while (cur != NULL) {
    //Serial.print("checking segment at "); Serial.print(cur->x); Serial.print(","); Serial.print(cur->y);
    if (cur->x == x &&  cur->y == y) {
      //Serial.println("...COLLIDE");
      return true;
    } else {
      //Serial.println("...OK");
      cur = cur->next;
    }
  }
  return false;
}

String Snake::toString() {
  String ret = "Snake --Size: " + snakeSize;
  ret = ret + " Segments: ";
  Segment *cur = head;
  while (cur != NULL) {
    ret = ret + "(" + cur->x + "," + cur->y + ")";
    cur = cur->next;
  }
  return ret;
}

void Snake::destruct() {
  Segment *cur = head;
  while(cur->next != NULL) {
    Segment *newCur = cur->next;
    delete cur;
    cur = newCur;
  }
  delete cur->next;
  delete cur;
 }
