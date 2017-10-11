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
    addWorldElement(p);

    TestGravity* tg = new TestGravity();
    tg->addWorldElement(p);
    addForce(tg);

    Sprite *block = new Sprite("./Ressources/sprite.png", Vector2d(10, 40), Vector2d(40, 40), Vector2d(400, 60));
    block->setPosition(Vector2d(100, 300));
    addWorldElement(block);

    Collider *colPerso =  new Collider(p);
    colPerso->initRectangular(0, 0, p->getSize().x, p->getSize().y);
    Collider *colBlock =  new Collider(block);
    colBlock->initRectangular(0, 0, block->getSize().x, block->getSize().y);
    addCollider(0, colPerso);
    addCollider(0, colBlock);

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
