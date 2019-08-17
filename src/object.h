#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    int spriteId;
    int x; //position
    int y; //position

    Object(int newSpriteId, int newX, int newY);
};

#endif