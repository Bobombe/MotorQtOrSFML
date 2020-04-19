#ifndef METALBACKSPRITE_H
#define METALBACKSPRITE_H

#include "Sprite.h"


class MetalBackSprite : public Sprite
{

protected:
    // Definition of wall sprite
    static const std::string SPRITE1_PATH;
    static const Vector2d BACK_POS;
    static const Vector2d BACK_SIZE;

public:
    MetalBackSprite(int nbRepeatWidth = 1, int nbRepeatHight = 1);
};

#endif // METALBACKSPRITE_H
