
#include "Mot/Sprite.h"
#include "Mot/KeyboardListener.h"
#include "Mot/MouseListener.h"

#ifndef SRC_PERSOTEST_H_
#define SRC_PERSOTEST_H_

class PersoTest : public Sprite, public KeyboardListener, public MouseListener
{
protected:
	Vector2d _mousePos;
	double _trust;
public:
	PersoTest();
	virtual ~PersoTest();

    virtual int update(double seconds);
	virtual void mouseMoved(Vector2d pos);
    virtual void keyPressed(Key::Key key);
    virtual void keyReleased(Key::Key key);
};

#endif
