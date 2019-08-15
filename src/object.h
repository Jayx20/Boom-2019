#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    int spriteId;
    float x; //position
    float y; //position

    Object(int newSpriteId, float newX, float newY);
};

#endif