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

StartScreen::StartScreen() : Screen()
{
    _pos.y = -Moteur2D::getInstance()->getScreenSize().y;
    _speed.y = 400;
    addWorldElement(new Sprite("./Ressources/Fond3.png"));
    PersoTest* p = new PersoTest();
    addWorldElement(p);
    TestGravity* tg = new TestGravity();
    tg->addWorldElement(p);
    addForce(tg);

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
