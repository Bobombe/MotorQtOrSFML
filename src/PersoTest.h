
#include "Mot/AnimatedSprite.h"
#include "Mot/KeyboardListener.h"
#include "Mot/MouseListener.h"

#ifndef SRC_PERSOTEST_H_
#define SRC_PERSOTEST_H_

class PersoTest : public AnimatedSprite, public KeyboardListener, public MouseListener
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

protected:
    virtual int update(double seconds);
};

#endif
