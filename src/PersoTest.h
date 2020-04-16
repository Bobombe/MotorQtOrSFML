
#include "AnimatedSprite.h"
#include "MouseAndKeyListener.h"
#include "Camera.h"

#ifndef SRC_PERSOTEST_H_
#define SRC_PERSOTEST_H_

class PersoTest : public AnimatedSprite, public MouseAndKeyListener
{
protected:
    enum CharacterState {
        STANDING_RIGHT = 0,
        STANDING_LEFT,
        RUNNING_RIGHT,
        RUNNING_LEFT,
        PUSHING_RIGHT,
        PUSHING_LEFT,
        STOPPING_RIGHT,
        STOPPING_LEFT,
        JUMPING_RIGHT,
        JUMPING_LEFT
    };

	Vector2d _mousePos;
	double _trust;

	// For movement
	CharacterState _state;
	bool _movingLeft;
	bool _movingRight;
	bool _jump;

	double _onGround; // Store the y position when on ground

	Camera * _camera;

public:
	PersoTest();
	virtual ~PersoTest();

	virtual void mouseMoved(Vector2d pos);
    virtual void keyPressed(Key::Key key);
    virtual void keyReleased(Key::Key key);

    virtual void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...);

    void setCamera(Camera *camera);

protected:
    virtual int update(double seconds);
    virtual int draw();
};

#endif
