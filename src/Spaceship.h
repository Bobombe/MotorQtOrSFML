
#include "Sprite.h"
#include "MouseAndKeyListener.h"
#include "Planet.h"


#ifndef SRC_SPACESHIP_H_
#define SRC_SPACESHIP_H_

class Pod;

class Spaceship : public Sprite, public MouseAndKeyListener
{
protected:

	// For movement
	bool _movingLeft;
	bool _movingRight;
	bool _movingUp;
	bool _movingDown;

	bool _firing;

	double _fireCoolDown;

	double _invincible;
	double _usingEnergy;

	std::vector<Vector2d> _dockPositions;
	std::vector< Pod * > _docks;

	double _maxAccel;
	double _maxSpeed;
	double _minPosX;
	double _maxPosX;
	double _minPosY;
	double _maxPosY;

	int _nbPodDocked;

	int _credits;
	int _power;

public:
    struct PassengerStats {
        int happiness;
        Planet::PlanetType color;
    };
	Spaceship();
	virtual ~Spaceship();

	virtual void mouseMoved(Vector2d pos);
    virtual void keyPressed(Key::Key key);
    virtual void keyReleased(Key::Key key);

    virtual void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...);

    bool getDockPosition(Pod * dockingPod, Vector2d& dockPosition);

    void updateMovements();

    void getStats(int& credits, int& power, std::vector<PassengerStats>& passengersHappiness);

protected:
    virtual int update(double seconds);
    virtual int draw();
};

#endif
