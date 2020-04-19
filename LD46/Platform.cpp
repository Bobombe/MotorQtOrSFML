#include "Platform.h"

const std::string Platform::SPRITE1_PATH = "Ressources/sprite1.png";
const Vector2d Platform::PLATFORM_POS = Vector2d(240, 640);
const Vector2d Platform::PLATFORM_SIZE = Vector2d(120, 11);

Platform::Platform(int nbCentralSection) :
    Sprite(SPRITE1_PATH, PLATFORM_POS, PLATFORM_SIZE, Vector2d(PLATFORM_SIZE.x*nbCentralSection, PLATFORM_SIZE.y))
{

}
