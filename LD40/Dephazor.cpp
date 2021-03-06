#include "Dephazor.h"
#include "Opponent.h"
#include "Collider.h"
#include "ScreenLevel1.h"

Dephazor::Dephazor(WorldElement * parent) : Sprite("./Ressources/dephazor.png"), _dead(false)
{
    _weName = "Dephazor";
    _collider =  new Collider(this);
    _collider->initRectangular(0, 0, getSize().x, getSize().y);
    setSpeed(Vector2d(0, -900));
    setParent(parent);
    ScreenLevel1 * screen = dynamic_cast<ScreenLevel1*>(parent);
    if (screen) {
        screen->addCollider(0, _collider);
    } else {
        std::cout << "Problem in Dephazor::Dephazor " << std::endl;
    }
}

Dephazor::~Dephazor()
{
    ScreenLevel1 * screen = dynamic_cast<ScreenLevel1*>(_parent);
    if (screen) {
        screen->deleteCollider(0, _collider);
    } else {
        std::cout << "Problem in Dephazor::~Dephazor " << std::endl;
    }
}

int Dephazor::update(double seconds)
{
    Sprite::update(seconds);
    if (_dead || (getAbsolutePosition().y < -getAbsoluteSize().y)) {
        delete this;
    }
    return 0;
}

void Dephazor::handleCollisionWith(WorldElement * weColided, double, int...)
{
    Opponent * opp = dynamic_cast<Opponent*>(weColided);
    if (opp) {
        _dead = true;
    }
}



