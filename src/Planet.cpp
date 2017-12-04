#include "Planet.h"
#include "ScreenLevel1.h"

Planet::Planet(PlanetType podType, bool left, WorldElement * parent) : Sprite(), _planetType(podType), _cabCaller(0), _freeCab(false)
{
    setParent(parent);

    double baseSpeed = 100;
    switch (_planetType) {
    case PLANET_PURPLE:
        if (left) {
            setSprite("./resLD40/planets.png", Vector2d(200, 0), Vector2d(200, 600));
        } else{
            setSprite("./resLD40/planets.png", Vector2d(0, 0), Vector2d(200, 600));
        }
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(0, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case PLANET_ORANGE:
        if (left) {
            setSprite("./resLD40/planets.png", Vector2d(600, 0), Vector2d(200, 600));
        } else{
            setSprite("./resLD40/planets.png", Vector2d(400, 0), Vector2d(200, 600));
        }
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(10, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case PLANET_GREEN:
        if (left) {
            setSprite("./resLD40/planets.png", Vector2d(1000, 0), Vector2d(200, 600));
        } else{
            setSprite("./resLD40/planets.png", Vector2d(800, 0), Vector2d(200, 600));
        }
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(20, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case PLANET_YELLOW:
        if (left) {
            setSprite("./resLD40/planets.png", Vector2d(1400, 0), Vector2d(200, 600));
        } else{
            setSprite("./resLD40/planets.png", Vector2d(1200, 0), Vector2d(200, 600));
        }
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(30, 0), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case PLANET_WHITE:
        if (left) {
            setSprite("./resLD40/planets.png", Vector2d(1800, 0), Vector2d(200, 600));
        } else{
            setSprite("./resLD40/planets.png", Vector2d(1600, 0), Vector2d(200, 600));
        }
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(0, 60), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    case PLANET_BLACK:
        if (left) {
            setSprite("./resLD40/planets.png", Vector2d(2200, 0), Vector2d(200, 600));
        } else{
            setSprite("./resLD40/planets.png", Vector2d(2000, 0), Vector2d(200, 600));
        }
        setSpeed(Vector2d(0, baseSpeed));
        _cabCaller = new Obstacle("./resLD40/palette.png", Vector2d(20, 60), Vector2d(10, 10), Vector2d(200, 10), this);
        break;
    }

    if (!left) {
        setPosition(Vector2d(ScreenLevel1::SIZEX-200, -getAbsoluteSize().y));
        _cabCaller->setPosition(Vector2d(50-_cabCaller->getSize().x, 300));
    } else {
        setPosition(Vector2d(0, -getAbsoluteSize().y));
        _cabCaller->setPosition(Vector2d(getSize().x-50, 300));
    }
}

Planet::~Planet()
{
}

int Planet::update(double seconds)
{
    if (_freeCab && _cabCaller) {
        delete _cabCaller;
        _cabCaller = 0;
        _freeCab = false;
    }
    Sprite::update(seconds);
    return 0;
}

void Planet::freeBlock()
{
    _freeCab = true;
}
