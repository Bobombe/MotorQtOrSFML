#ifndef PLATFORM_H
#define PLATFORM_H

#include "Sprite.h"

class Platform : public Sprite
{

protected:
    // Definition of wall sprite
    static const std::string SPRITE1_PATH;
    static const Vector2d PLATFORM_POS;
    static const Vector2d PLATFORM_SIZE;

public:
    Platform(int nbCentralSection = 1);
};

#endif // PLATFORM_H
