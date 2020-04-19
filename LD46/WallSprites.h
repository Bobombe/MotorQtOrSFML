#ifndef WALLSPRITES_H
#define WALLSPRITES_H

#include "Sprite.h"

class WallSprites : public Sprite
{
public:
    enum WallType {
        WALL_LEFT,
        WALL_RIGHT,
        WALL_TOP,   //// Ceiling
        WALL_BOTTOM //// Floor
    };

protected:
    // Definition of wall sprite
    static const std::string SPRITE1_PATH;
    static const Vector2d WALL_POS;
    static const Vector2d WALL_SIZE;

    WallType _wallType{WALL_BOTTOM};

public:
    WallSprites(int length = 1);
    WallSprites(WallType wallType, int length = 1);
};

#endif // WALLSPRITES_H
