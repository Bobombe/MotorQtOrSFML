
#include "GPScreen.h"
#include "moteur2d.h"
#include "GPCharacter.h"
#include "GPGravity.h"
#include "Collider.h"
#include "Text.h"
#include "GPCamera.h"

GPScreen::GPScreen() : Screen()
{
    _weName = "GPScreen";
    Sprite *s = new Sprite("./Ressources/Fond3.png");

    // Create character
    GPCharacter* p = new GPCharacter();
    p->setPosition(Vector2d(200, 160));
    p->setParent(this);
    addCollider(0, p->getCollider());
    p->setScreenId(0);
    _camera = new GPCamera(this, p);
    s->setParent(_camera);

    // Create Gravity
    GPGravity* tg = new GPGravity();
    tg->addWorldElement(p);
    addForce(tg);

    // Platforms
    addPlatform(-300, 200, 10);
    addPlatform(-100, 250, 10);
    addPlatform(100, 300, 10);
    addPlatform(300, 350, 10);
    addPlatform(600, 400, 10);
    addPlatform(900, 450, 10);

}

GPScreen::~GPScreen()
{
}


int GPScreen::draw()
{
    int retValue = 0;
    if (_bt.isActivated()) {
        retValue = 1;
    }
    Screen::draw();
    return retValue;
}

void GPScreen::addPlatform(int posx, int posy, int width, int hight)
{

    // First Platform
    Sprite *block = new Sprite("./Ressources/sprite.png", Vector2d(10, 40), Vector2d(40, 40), Vector2d(width*40, hight*20));
    block->setPosition(Vector2d(posx, posy));
    block->setParent(this);
    // First Platform Collider
    Collider *colBlock =  new Collider(block);
    colBlock->initRectangular(0, 0, block->getSize().x, block->getSize().y);
    addCollider(0, colBlock);
}
