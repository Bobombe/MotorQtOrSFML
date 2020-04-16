#include "Opponent.h"
#include "Pod.h"
#include "Collider.h"
#include "ScreenLevel1.h"
#include "moteur2d.h"
#include <stdlib.h>     /* srand, rand */

    const int Pod::BASESPEED(100);
    const int Pod::BASEACCEL(100);
Pod::Pod(Spaceship * player, Planet::PlanetType podType, bool left, WorldElement * parent) : Sprite(), _podType(podType), _player(player),
                _planet(0), _cabCaller(0), _dead(false), _state(STATE_NONE)
{
    _weName = "Pod";
    setParent(parent);

    double baseSpeed = 100;
    switch (_podType) {
    case Planet::PLANET_PURPLE:
        setSprite("./resLD40/cars.png", Vector2d(0, 100), Vector2d(20, 30));
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(0, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case Planet::PLANET_ORANGE:
        setSprite("./resLD40/cars.png", Vector2d(20, 100), Vector2d(20, 30));
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(10, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case Planet::PLANET_GREEN:
        setSprite("./resLD40/cars.png", Vector2d(40, 100), Vector2d(20, 30));
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(20, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case Planet::PLANET_YELLOW:
        setSprite("./resLD40/cars.png", Vector2d(60, 100), Vector2d(20, 30));
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(30, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case Planet::PLANET_WHITE:
        setSprite("./resLD40/cars.png", Vector2d(80, 100), Vector2d(20, 30));
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(0, 60), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case Planet::PLANET_BLACK:
        setSprite("./resLD40/cars.png", Vector2d(100, 100), Vector2d(20, 30));
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(20, 60), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    }

    _collider =  new Collider(this);
    _collider->initRectangular(0, 0, getSize().x, getSize().y);

    if (!left) {
        setPosition(Vector2d(ScreenLevel1::SIZEX-20, -getAbsoluteSize().y));
        _cabCaller->setPosition(Vector2d(-_cabCaller->getSize().x, 10));
    } else {
        setPosition(Vector2d(0, -getAbsoluteSize().y));
        _cabCaller->setPosition(Vector2d(getSize().x, 10));
    }

    ScreenLevel1 * screen = dynamic_cast<ScreenLevel1*>(parent);
    if (screen) {
        screen->addCollider(0, _collider);
    } else {
        std::cout << "Problem in Pod::Pod " << std::endl;
    }
}

Pod::~Pod()
{
    ScreenLevel1 * screen = dynamic_cast<ScreenLevel1*>(_player->getParent());
    if (screen) {
        screen->deleteCollider(0, _collider);
    } else {
        std::cout << "Problem in Pod::~Pod " << std::endl;
    }
}

int Pod::update(double seconds)
{
    if (_dead) {
        if(getAbsolutePosition().x>ScreenLevel1::SIZEX/2-20) {
            setSpeed(Vector2d(500, 0));
        } else {
            setSpeed(Vector2d(-500, 0));
        }
    }
    if (_state == STATE_DOCKING) {
        Vector2d speed = _dockPosition+_player->getAbsolutePosition()-getAbsolutePosition();
        if (speed.x < 1 && speed.x > -1 && speed.y < 1 && speed.y > -1) {
            setParent(_player);
            setPosition(_dockPosition);
            setSpeed(Vector2d());
        } else {
            Vector2d unit = speed;
            speed*=2;
            unit.normalize();
            speed+=unit*2;
            setSpeed(speed);
        }
        if (_cabCaller) {
            delete _cabCaller;
            _cabCaller = 0;
        }
    } else if (_state == STATE_GOING) {
        if (_planet){
            Vector2d speed = _planet->getAbsolutePosition()+Vector2d(100, 300)-getAbsolutePosition();
            setSpeed(speed);
        }
    }
    Sprite::update(seconds);
    if (getAbsolutePosition().y > Moteur2D::getInstance()->getScreenSize().y ||
        getAbsolutePosition().x > Moteur2D::getInstance()->getScreenSize().x || getAbsolutePosition().x < -getSize().x) {
        delete this;
    }
    return 0;
}
void Pod::acceptCall()
{
    if (_state == STATE_NONE) {
        if (_player->getDockPosition(this, _dockPosition)) {
            _state = STATE_DOCKING; //State docking
        }
    }
}


void Pod::handleCollisionWith(WorldElement * weColided, double, int...)
{
    Spaceship * ship = dynamic_cast<Spaceship*>(weColided);
    if (ship) {
        acceptCall();
    }
}


int Pod::undock(Planet * planet)
{
    int ret = -1;
    if (planet->_planetType == _podType) {
        ret = 5;
        _planet = planet;
        setParent(_planet);
        _state = STATE_GOING;
    }
    return ret;
}





