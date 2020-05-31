#include "Opponent.h"
#include "Dephazor.h"
#include "Spaceship.h"
#include "Collider.h"
#include "ScreenLevel1.h"
#include "moteur2d.h"
#include <stdlib.h>     /* srand, rand */

    const int Opponent::BASESPEED(100);
    const int Opponent::BASEACCEL(100);
Opponent::Opponent(Spaceship * player, OpponentType oppType, WorldElement * parent) : Sprite(), _oppType(oppType), _player(player),
                _movingLeft(false), _movingRight(false), _movingUp(false), _movingDown(false), _dead(false), _state(0)
{
    _weName = "Opponent";
    _state = rand() % 2 + 1;

    double baseSpeed = 100;
    switch (_oppType) {
    case OPP_PURPLE:
        setSprite("./Ressources/cars.png", Vector2d(0, 0), Vector2d(40, 50));
        setSpeed(Vector2d(0, baseSpeed));
        break;
    case OPP_ORANGE:
        setSprite("./Ressources/cars.png", Vector2d(40, 0), Vector2d(40, 50));
        setSpeed(Vector2d(0, baseSpeed*1.5));
        _movingLeft = true;
        break;
    case OPP_GREEN:
        setSprite("./Ressources/cars.png", Vector2d(80, 0), Vector2d(40, 50));
        setSpeed(Vector2d(0, baseSpeed*4));
        break;
    case OPP_YELLOW:
        setSprite("./Ressources/cars.png", Vector2d(80, 50), Vector2d(40, 50));
        setSpeed(Vector2d(0, baseSpeed*2));
        break;
    case OPP_WHITE:
        setSprite("./Ressources/cars.png", Vector2d(0, 50), Vector2d(40, 50));
        setSpeed(Vector2d(0, baseSpeed*5));
        break;
    case OPP_BLACK:
        setSprite("./Ressources/cars.png", Vector2d(40, 50), Vector2d(40, 50));
        setSpeed(Vector2d(0, baseSpeed*0.5));
        _movingRight = true;
        break;
    }

    _collider =  new Collider(this);
    _collider->initRectangular(0, 0, getSize().x, getSize().y);
    setParent(parent);
    ScreenLevel1 * screen = dynamic_cast<ScreenLevel1*>(parent);
    if (screen) {
        screen->addCollider(0, _collider);
    } else {
        std::cout << "Problem in Opponent::Opponent " << std::endl;
    }
    setPosition(Vector2d(ScreenLevel1::SIZEX/2, -getAbsoluteSize().y));
}

Opponent::~Opponent()
{
    ScreenLevel1 * screen = dynamic_cast<ScreenLevel1*>(_parent);
    if (screen) {
        screen->deleteCollider(0, _collider);
    } else {
        std::cout << "Problem in Opponent::~Opponent " << std::endl;
    }
}

int Opponent::update(double seconds)
{
    if (_dead) {
        if(getAbsolutePosition().x>ScreenLevel1::SIZEX/2-20) {
            setSpeed(Vector2d(500, 0));
        } else {
            setSpeed(Vector2d(-500, 0));
        }
    } else {
        int baseSpeed = 100;
        int baseAccel = 100;
        Vector2d speed = getSpeed();
        Vector2d accel = getAcceleration();
        switch (_oppType) {
        case OPP_PURPLE:
            if (_state == 1 && getAbsolutePosition().x>ScreenLevel1::SIZEX/10-20) {
                speed.x = -baseSpeed;
            } else if (_state == 2 && getAbsolutePosition().x<ScreenLevel1::SIZEX/5*4.5-20) {
                speed.x = baseSpeed;
            } else {
                speed.x = 0;
            }
            break;
        case OPP_ORANGE: {
            double mini = 0;
            double maxi = ScreenLevel1::SIZEX-40;
            double ptLeft = ScreenLevel1::SIZEX/5.;
            double ptRight = ptLeft*4 - getAbsoluteSize().x;
            if (_movingLeft && getAbsolutePosition().x < ptLeft) {
                _movingLeft = false;
                _movingRight = true;
            } else if (_movingRight && getAbsolutePosition().x > ptRight) {
                _movingLeft = true;
                _movingRight = false;
            }
            if (_movingLeft) {
                double maxSpeed = -baseSpeed*2;
                if (speed.x < maxSpeed) {
                    speed.x = maxSpeed;
                    accel.x = 0;
                } else {
                    accel.x = maxSpeed*(2.*-maxSpeed+1.)/(2.*(maxi-ptRight));//-baseAccel*4;
                }
            } else {
                double maxSpeed = baseSpeed*2;
                if (speed.x > maxSpeed) {
                    speed.x = maxSpeed;
                    accel.x = 0;
                } else {
                    accel.x = maxSpeed*(2.*-maxSpeed+1.)/(2.*(mini-ptLeft));//baseAccel*4;
                }
            }
            break;
        }
        case OPP_GREEN:
            if (getAbsolutePosition().x > _player->getAbsolutePosition().x) {
                accel.x = baseAccel*4;
                if (getAbsolutePosition().x > ScreenLevel1::SIZEX*0.9) {
                    accel.x = 0;
                    speed.x = 0;
                }
            } else {
                accel.x = -baseAccel*4;
                if (getAbsolutePosition().x < ScreenLevel1::SIZEX/10) {
                    accel.x = 0;
                    speed.x = 0;
                }
            }
            if (speed.x < -baseSpeed*3) {
                speed.x = -baseSpeed*3;
                accel.x = 0;
            } else if (speed.x > baseSpeed*3) {
                speed.x = baseSpeed*3;
                accel.x = 0;
            }
            break;
        case OPP_YELLOW:
            if (getAbsolutePosition().x > _player->getAbsolutePosition().x) {
                accel.x = -baseAccel*2;
                if (getAbsolutePosition().x > ScreenLevel1::SIZEX*0.9) {
                    accel.x = 0;
                    speed.x = 0;
                }
            } else {
                accel.x = baseAccel*2;
                if (getAbsolutePosition().x < ScreenLevel1::SIZEX/10) {
                    accel.x = 0;
                    speed.x = 0;
                }
            }
            if (speed.x < -baseSpeed*2) {
                speed.x = -baseSpeed*2;
                accel.x = 0;
            } else if (speed.x > baseSpeed*2) {
                speed.x = baseSpeed*2;
                accel.x = 0;
            }
            break;
        case OPP_WHITE:

            break;
        case OPP_BLACK:
            if (_movingLeft && getAbsolutePosition().x < ScreenLevel1::SIZEX*0.3) {
                _movingLeft = false;
                _movingRight = true;
            } else if (_movingRight && getAbsolutePosition().x > (ScreenLevel1::SIZEX*0.7 - getAbsoluteSize().x)) {
                _movingLeft = true;
                _movingRight = false;
            }
            if (_movingLeft) {
                if (speed.x < -baseSpeed*4) {
                    speed.x = -baseSpeed*4;
                    accel.x = 0;
                } else {
                    accel.x = -baseAccel*4;
                }
            } else {
                if (speed.x > baseSpeed*4) {
                    speed.x = baseSpeed*4;
                    accel.x = 0;
                } else {
                    accel.x = baseAccel*4;
                }
            }
            break;
        }
        setSpeed(speed);
        setAcceleration(accel);
    }
    Sprite::update(seconds);
    if (getAbsolutePosition().y > Moteur2D::getInstance()->getScreenSize().y ||
        getAbsolutePosition().x > Moteur2D::getInstance()->getScreenSize().x || getAbsolutePosition().x < -getSize().x) {
        delete this;
    }
    return 0;
}


void Opponent::handleCollisionWith(WorldElement * weColided, double, int...)
{
    Dephazor * dephazor = dynamic_cast<Dephazor*>(weColided);
    Spaceship * ship = dynamic_cast<Spaceship*>(weColided);
    if (dephazor || ship) {
        _dead = true;
    }
}
