#include "MetalBackSprite.h"

const std::string MetalBackSprite::SPRITE1_PATH = "Ressources/sprite1.png";
const Vector2d MetalBackSprite::BACK_POS = Vector2d(160, 120);
const Vector2d MetalBackSprite::BACK_SIZE = Vector2d(80, 80);

MetalBackSprite::MetalBackSprite(int nbRepeatWidth, int nbRepeatHight) :
    Sprite(SPRITE1_PATH, BACK_POS, BACK_SIZE, Vector2d(BACK_SIZE.x*nbRepeatWidth, BACK_SIZE.y*nbRepeatHight))
{

}
