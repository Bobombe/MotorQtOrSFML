/*
 * StartScreenLD40.cpp
 *
 *  Created on: Oct 20, 2016
 *      Author: dev
 */

#include "StartScreenLD40.h"
#include "moteur2d.h"
#include "Collider.h"
#include "Text.h"

StartScreenLD40::StartScreenLD40() : Screen(), _btStart("./Ressources/spaceship.png", Vector2d(0, 0), Vector2d(60, 80),
                                            "./Ressources/spaceship.png", Vector2d(0, 0), Vector2d(60, 80))
{
    _weName = "StartScreenLD40";
    Sprite *s = new Sprite("./Ressources/FondStartScreenLD40.png");
    s->setParent(this);
    s->setScale(1.3);
    s->setPosition(Vector2d(-66, 0));

    _btStart.setPosition(Vector2d(570, 500));
    _btStart.setScreenId(0);
    _btStart.setParent(this);

    Text * text = new Text("           Space Cab\n     Not finish at all :/\nClick on the car to begin", this);
    text->setPosition(Vector2d(150, 100));
    text->setCharacterSize(80);
    text->setColor(Color::Green);
    text->setStyle(Text::Bold | Text::Italic);
    setPosition(Vector2d(0, -1000));
    setSpeed(Vector2d(0, 300));
}

StartScreenLD40::~StartScreenLD40()
{
}


int StartScreenLD40::draw()
{
    int retValue = 0;
    if (getPosition().y>=0) {
        setSpeed(Vector2d(0, 0));
        setPosition(Vector2d(0, 0));
        // retValue = 1;
    }
    if (_btStart.isActivated()) {
        retValue = 1;
    }
    Screen::draw();
    return retValue;
}
