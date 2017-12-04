#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Sprite.h"
#include "Screen.h"


class Obstacle : public Sprite
{
protected:

public:
    Obstacle(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, WorldElement * parent);
    Obstacle(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, Vector2d spriteSize, WorldElement * parent);
    virtual ~Obstacle();
};

#endif // OBSTACLE_H
