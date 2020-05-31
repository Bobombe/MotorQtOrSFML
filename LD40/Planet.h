#ifndef PLANET_H
#define PLANET_H

#include "Obstacle.h"

class Planet : public Sprite
{
public:

    enum PlanetType {
        PLANET_PURPLE = 0,
        PLANET_ORANGE = 1,
        PLANET_GREEN = 2,
        PLANET_YELLOW = 3,
        PLANET_WHITE = 4,
        PLANET_BLACK = 5
    };
    PlanetType _planetType;

protected:

    Obstacle * _cabCaller;
    bool _freeCab;


public:
    Planet(PlanetType oppType, bool left, WorldElement * parent);
    virtual ~Planet();

    virtual int update(double seconds);
    void freeBlock();

};

#endif // PLANET_H
