#include <iostream>
#include "object.h"

extern const int NUM_SPRITES;

Object::Object(int newSpriteId, int newX, int newY) {
    //checks to make sure the sprite id is valid
    if(newSpriteId > NUM_SPRITES-1) {printf("Object created with invalid sprite ID!"); spriteId=0;}
    else {spriteId = newSpriteId;}
    
    x = newX;
    y = newY;
}