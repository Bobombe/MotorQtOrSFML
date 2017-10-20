/*
 * StartScreen.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: dev
 */

#include "StartScreen.h"
#include "Mot/moteur2d.h"
#include "PersoTest.h"
#include "TestGravity.h"
#include "Mot/Collider.h"

StartScreen::StartScreen() : Screen()
{
    _pos.y = -10;//Moteur2D::getInstance()->getScreenSize().y;
    _speed.y = 400;
    addWorldElement(new Sprite("./Ressources/Fond3.png"));

    PersoTest* p = new PersoTest();
    p->setPosition(Vector2d(200, 180));
    addWorldElement(p);
    addCollider(0, p->getCollider());
    p->setScreenId(0);

    TestGravity* tg = new TestGravity();
    tg->addWorldElement(p);
    addForce(tg);

    Sprite *block = new Sprite("./Ressources/sprite.png", Vector2d(10, 40), Vector2d(40, 40), Vector2d(400, 60));
    block->setPosition(Vector2d(100, 300));
    addWorldElement(block);

    Collider *colBlock =  new Collider(block);
    colBlock->initRectangular(0, 0, block->getSize().x, block->getSize().y);
    addCollider(0, colBlock);

    Sprite *block2 = new Sprite("./Ressources/sprite.png", Vector2d(10, 40), Vector2d(40, 40), Vector2d(40, 100));
    block2->setPosition(Vector2d(500, 180));
    addWorldElement(block2);
    Collider *colBlock2 =  new Collider(block2);
    colBlock2->initRectangular(0, 0, block2->getSize().x, block2->getSize().y);
    addCollider(0, colBlock2);

    Sprite *block3 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(40, 100));
    block3->setPosition(Vector2d(100, 180));
    addWorldElement(block3);
    Collider *colBlock3 =  new Collider(block3);
    colBlock3->initRectangular(0, 0, block3->getSize().x, block3->getSize().y);
    addCollider(0, colBlock3);

    Sprite *block4 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(800, 100));
    block4->setPosition(Vector2d(100, 500));
    addWorldElement(block4);
    Collider *colBlock4 =  new Collider(block4);
    colBlock4->initRectangular(0, 0, block4->getSize().x, block4->getSize().y);
    addCollider(0, colBlock4);

    Sprite *block5 = new Sprite("./Ressources/sprite.png", Vector2d(30, 50), Vector2d(10, 10), Vector2d(40, 50));
    block5->setPosition(Vector2d(300, 240));
    addWorldElement(block5);
    Collider *colBlock5 =  new Collider(block5);
    colBlock5->initRectangular(0, 0, block5->getSize().x, block5->getSize().y);
    addCollider(0, colBlock5);

}

StartScreen::~StartScreen()
{
}


int StartScreen::draw(Vector2d pos)
{
    int retValue = 0;
    if (_pos.y>=0)
    {
        setSpeed(Vector2d(0, 0));
        _pos.y=0;
        retValue = 1;
    }
    Screen::draw(pos);
    return retValue;
}
