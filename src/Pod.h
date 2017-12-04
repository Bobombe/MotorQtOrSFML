#ifndef SRC_POD_H
#define SRC_POD_H

#include "Mot/Obstacle.h"
#include "Spaceship.h"
#include "Planet.h"


class Pod : public Sprite
{
public:

    static const int BASESPEED;
    static const int BASEACCEL;

protected:

    enum PodState {
        STATE_NONE,
        STATE_LEFT,
        STATE_RIGHT,
        STATE_DOCKING,
        STATE_DOCKED,
        STATE_GOING
    };

    Planet::PlanetType _podType;
    Spaceship * _player;
    Planet * _planet;
    Obstacle * _cabCaller;

	bool _dead;

	PodState _state;
	Vector2d _dockPosition;


public:
    Pod(Spaceship * player, Planet::PlanetType oppType, bool left, WorldElement * parent);
    virtual ~Pod();

    virtual int update(double seconds);
    void acceptCall();

    virtual void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...);

    int undock(Planet * planet);

};

#endif // POD_H
