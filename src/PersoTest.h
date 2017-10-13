
#include "Mot/AnimatedSprite.h"
#include "Mot/MouseAndKeyListener.h"

#ifndef SRC_PERSOTEST_H_
#define SRC_PERSOTEST_H_

class PersoTest : public AnimatedSprite, public MouseAndKeyListener
{
protected:
	Vector2d _mousePos;
	double _trust;
public:
	PersoTest();
	virtual ~PersoTest();

	virtual void mouseMoved(Vector2d pos);
    virtual void keyPressed(Key::Key key);
    virtual void keyReleased(Key::Key key);

    virtual void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...);

protected:
    virtual int update(double seconds);
};

#endif
