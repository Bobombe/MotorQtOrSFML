#include "WallSprites.h"

const std::string WallSprites::SPRITE1_PATH = "Ressources/sprite1.png";
const Vector2d WallSprites::WALL_POS = Vector2d(160, 680);
const Vector2d WallSprites::WALL_SIZE = Vector2d(40, 40);

WallSprites::WallSprites(int length) : Sprite(SPRITE1_PATH, WALL_POS, WALL_SIZE, Vector2d(WALL_SIZE.x*length, WALL_SIZE.y))
{
    setScale(2);
}

WallSprites::WallSprites(WallType wallType, int length) : Sprite(SPRITE1_PATH, WALL_POS, WALL_SIZE, Vector2d(WALL_SIZE.x*length, WALL_SIZE.y))
{
    setScale(2);
    switch (wallType) {
    case WALL_LEFT:
        setRotation(90);
        setRefPoint(Vector2d(0, getSize().y));
        break;
    case WALL_RIGHT:
        setRotation(-90);
        setRefPoint(Vector2d(getSize().x, 0));
        break;
    case WALL_TOP:
        setRotation(180);
        setRefPoint(getSize());
        break;
    case WALL_BOTTOM:
        break;
    }
}
