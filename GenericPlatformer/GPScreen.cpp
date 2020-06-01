
#include "GPScreen.h"
#include "moteur2d.h"
#include "GPCharacter.h"
#include "GPGravity.h"
#include "Collider.h"
#include "Text.h"

GPScreen::GPScreen() : Screen()
{
    _weName = "GPScreen";
    Sprite *s = new Sprite("./Ressources/Fond3.png");
    s->setParent(this);

    GPCharacter* p = new GPCharacter();
    p->setPosition(Vector2d(200, 160));
    p->setParent(this);
    addCollider(0, p->getCollider());
    p->setScreenId(0);

    GPGravity* tg = new GPGravity();
    tg->addWorldElement(p);
    addForce(tg);

    Sprite *block = new Sprite("./Ressources/sprite.png", Vector2d(10, 40), Vector2d(40, 40), Vector2d(400, 60));
    block->setPosition(Vector2d(100, 300));
    block->setParent(this);

    Collider *colBlock =  new Collider(block);
    colBlock->initRectangular(0, 0, block->getSize().x, block->getSize().y);
    addCollider(0, colBlock);

    Sprite *block4 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(800, 100));
    block4->setPosition(Vector2d(100, 500));
    block4->setParent(this);
    Collider *colBlock4 =  new Collider(block4);
    colBlock4->initRectangular(0, 0, block4->getSize().x, block4->getSize().y);
    addCollider(0, colBlock4);
/*
    Sprite *block2 = new Sprite("./Ressources/sprite.png", Vector2d(10, 40), Vector2d(40, 40), Vector2d(40, 100));
    block2->setPosition(Vector2d(500, 180));
    block2->setParent(this);
    Collider *colBlock2 =  new Collider(block2);
    colBlock2->initRectangular(0, 0, block2->getSize().x, block2->getSize().y);
    addCollider(0, colBlock2);

    Sprite *block3 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(40, 100));
    block3->setPosition(Vector2d(100, 180));
    block3->setParent(this);
    Collider *colBlock3 =  new Collider(block3);
    colBlock3->initRectangular(0, 0, block3->getSize().x, block3->getSize().y);
    addCollider(0, colBlock3);

    Sprite *block5 = new Sprite("./Ressources/sprite.png", Vector2d(30, 50), Vector2d(10, 10), Vector2d(40, 50));
    block5->setPosition(Vector2d(300, 240));
    block5->setParent(this);
    Collider *colBlock5 =  new Collider(block5);
    colBlock5->initRectangular(0, 0, block5->getSize().x, block5->getSize().y);
    addCollider(0, colBlock5);

    setScale(0.8);
    p->setScale(1.25);
//*/
}

GPScreen::~GPScreen()
{
}


int GPScreen::draw()
{
    int retValue = 0;
    if (getPosition().y>=20) {
        setSpeed(Vector2d(0, 0));
        setPosition(Vector2d(10, 20));
        // retValue = 1;
    }
    if (_bt.isActivated()) {
        retValue = 1;
    }
    Screen::draw();
    return retValue;
}
