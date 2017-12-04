#ifndef OPPONENT_H
#define OPPONENT_H

#include "Mot/Sprite.h"
#include "Spaceship.h"


class Opponent : public Sprite
{
public:

    static const int BASESPEED;
    static const int BASEACCEL;
    enum OpponentType {
        OPP_PURPLE,
        OPP_ORANGE,
        OPP_GREEN,
        OPP_YELLOW,
        OPP_WHITE,
        OPP_BLACK,
    };

protected:

    OpponentType _oppType;
    Spaceship * _player;
	// For movement
	bool _movingLeft;
	bool _movingRight;
	bool _movingUp;
	bool _movingDown;

	bool _dead;

	int _state;

    virtual void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...);


public:
    Opponent(Spaceship * player, OpponentType oppType, WorldElement * parent);
    virtual ~Opponent();

    virtual int update(double seconds);

};

#endif // OPPONENT_H
