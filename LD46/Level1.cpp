#include "Level1.h"
#include "moteur2d.h"
#include "Sound.h"

#include "WallSprites.h"
#include "MetalBackSprite.h"
#include "Platform.h"

Level1::Level1():
    Screen()
{
    MetalBackSprite* mbs = new MetalBackSprite(13, 8);
    mbs->setParent(this);
    mbs->setPosition(0, 10);

    /*
    Platform* platform1 = new Platform(1);
    platform1->setParent(this);
    platform1->setPosition(50, 500);

    Platform* platform2 = new Platform(1);
    platform2->setParent(this);
    platform2->setPosition(platform1->getPosition().x+platform1->getSize().x-5, platform1->getPosition().y);
    platform2->setRefPoint(Vector2d(3, 5));
    //platform2->setRotationSpeed(30);
    //*/

    WallSprites* wst = new WallSprites(WallSprites::WALL_TOP, 13);
    WallSprites* wsb = new WallSprites(WallSprites::WALL_BOTTOM, 13);
    wst->setParent(this);
    wsb->setParent(this);
    wst->setPosition(0, 0);
    wsb->setPosition(0, 640);

    _sadRobot.setParent(this);
    _sadRobot.setPosition(100, 500);

    _companioBall.setParent(this);
    _companioBall.setPosition(600, 500);

    _sadRobot.setCompanionBall(&_companioBall);
    _companioBall.setSadRobot(&_sadRobot);

    //_camera->setSpeed(Vector2d(10, 0));

}

Level1::~Level1()
{
}

void Level1::initScreen()
{
    _sadRobot.setScreenId(getScreenId());
    _companioBall.setScreenId(getScreenId());
}

int Level1::draw()
{
    int retValue = 0;
    Screen::draw();
    return retValue;
}
