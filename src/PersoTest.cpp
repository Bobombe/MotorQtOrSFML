
#include "PersoTest.h"
#include "Vector2d.h"
#include "Rectangle.h"
#include "moteur2d.h"

PersoTest::PersoTest() : AnimatedSprite("./Ressources/Perso.PNG"), _state(STANDING_RIGHT), _movingLeft(false), _movingRight(false),
                        _jump(false), _onGround(-1), _camera(0)
{
    _weName = "PersoTest";
	setPosition(Vector2d(100, 200));
	_mousePos = getPosition();
	_trust = 0;
	// Stand still
	addSubRect(STANDING_RIGHT, Rectangle(0, 60, 40, 60));
	setFramePerSecs(STANDING_RIGHT, 1);
	// run right
    addSubRect(RUNNING_RIGHT, Rectangle(40, 60, 40, 60));
    addSubRect(RUNNING_RIGHT, Rectangle(80, 60, 40, 60));
    addSubRect(RUNNING_RIGHT, Rectangle(120, 60, 40, 60));
    addSubRect(RUNNING_RIGHT, Rectangle(160, 60, 40, 60));
    addSubRect(RUNNING_RIGHT, Rectangle(200, 60, 40, 60));
    addSubRect(RUNNING_RIGHT, Rectangle(240, 60, 40, 60));
	setFramePerSecs(RUNNING_RIGHT, 12);
    // Jump right
    addSubRect(JUMPING_RIGHT, Rectangle(280, 60, 40, 60));
	setFramePerSecs(JUMPING_RIGHT, 1);
    // Stand still Left
    addSubRect(STANDING_LEFT, Rectangle(360, 0, 40, 60));
    setFramePerSecs(STANDING_LEFT, 1);
    // run left
    addSubRect(RUNNING_LEFT, Rectangle(120, 0, 40, 60));
    addSubRect(RUNNING_LEFT, Rectangle(160, 0, 40, 60));
    addSubRect(RUNNING_LEFT, Rectangle(200, 0, 40, 60));
    addSubRect(RUNNING_LEFT, Rectangle(240, 0, 40, 60));
    addSubRect(RUNNING_LEFT, Rectangle(280, 0, 40, 60));
    addSubRect(RUNNING_LEFT, Rectangle(320, 0, 40, 60));
    setFramePerSecs(RUNNING_LEFT, 12);
    // Jump left
    addSubRect(JUMPING_LEFT, Rectangle(80, 0, 40, 60));
    setFramePerSecs(JUMPING_LEFT, 1);
    // Stopping right
    addSubRect(STOPPING_RIGHT, Rectangle(40, 0, 40, 60));
    addSubRect(STOPPING_RIGHT, Rectangle(0, 0, 40, 60));
    setFramePerSecs(STOPPING_RIGHT, 6);
    // Stopping left
    addSubRect(STOPPING_LEFT, Rectangle(320, 60, 40, 60));
    addSubRect(STOPPING_LEFT, Rectangle(360, 60, 40, 60));
    setFramePerSecs(STOPPING_LEFT, 6);


    _collider =  new Collider(this);
    _collider->initRectangular(0, 0, getSize().x, getSize().y);
}

PersoTest::~PersoTest()
{
}


int PersoTest::update(double seconds)
{
    // Physics data of character
    int maxSpeed = 6, maxAccel = 40; // m/s
    int jumpAccel = 10;
    int pixPerMetre = 100;
    maxSpeed*=pixPerMetre;
    maxAccel*=pixPerMetre;
    jumpAccel*=pixPerMetre;

    jumpAccel = 800;

	double fixedThrust = 100;
	if (_trust) {
		_trust+= fixedThrust*seconds;
		Vector2d accelTrust = (_mousePos-getPosition());
		accelTrust.normalize();
		accelTrust*=_trust;
		moveAcceleration(accelTrust);
	}
    /////////////////////////////////////////
   //       DEPLACEMENTS HORIZONTAUX      //
  /////////////////////////////////////////
    Vector2d newSpeed = getSpeed();
    if (_movingRight && !_movingLeft) {
        newSpeed.x+=maxAccel*seconds;
        if (newSpeed.x>maxSpeed) {
            newSpeed.x=maxSpeed;
        }
        if(_onGround!=getPosition().y) {
            if (_state != JUMPING_RIGHT) {
                _state = JUMPING_RIGHT;
                setAnimation(JUMPING_RIGHT);
            }
        } else {
            if (newSpeed.x < 0) {
                if (_state != STOPPING_RIGHT) {
                    _state = STOPPING_RIGHT;
                    setAnimation(STOPPING_RIGHT);
                }
            } else {
                if (_state != RUNNING_RIGHT) {
                    _state = RUNNING_RIGHT;
                    setAnimation(RUNNING_RIGHT);
                }
            }
        }
    } else if (_movingLeft && !_movingRight) {
        newSpeed.x-=maxAccel*seconds;
        if (newSpeed.x<-maxSpeed) {
            newSpeed.x=-maxSpeed;
        }
        if(_onGround!=getPosition().y) {
            if (_state != JUMPING_LEFT) {
                _state = JUMPING_LEFT;
                setAnimation(JUMPING_LEFT);
            }
        } else {
            if (newSpeed.x > 0) {
                if (_state != STOPPING_LEFT) {
                    _state = STOPPING_LEFT;
                    setAnimation(STOPPING_LEFT);
                }
            } else {
                if (_state != RUNNING_LEFT) {
                    _state = RUNNING_LEFT;
                    setAnimation(RUNNING_LEFT);
                }
            }
        }
    } else { // Slowing
        if (newSpeed.x > 0) {
            //m_orienteDroite = true;
            newSpeed.x-=maxAccel/1.2*seconds;
            if (newSpeed.x<=0) {
                newSpeed.x=0;
                if (_onGround==getPosition().y && _state != STANDING_RIGHT) {
                    _state = STANDING_RIGHT;
                    setAnimation(STANDING_RIGHT);
                }
            } else if (_onGround==getPosition().y && _state != STOPPING_RIGHT) {
                _state = STOPPING_RIGHT;
                setAnimation(STOPPING_RIGHT);
            }
        } else if (newSpeed.x < 0) {
            //m_orienteDroite = false;
            newSpeed.x+=maxAccel/1.2*seconds;
            if (newSpeed.x>=0) {
                newSpeed.x=0;
                if (_onGround==getPosition().y && _state != STANDING_LEFT) {
                    _state = STANDING_LEFT;
                    setAnimation(STANDING_LEFT);
                }
            } else if (_onGround==getPosition().y && _state != STOPPING_LEFT) {
                _state = STOPPING_LEFT;
                setAnimation(STOPPING_LEFT);
            }
        }
    }
    /////////////////////////////////////////
    //        DEPLACEMENTS VERTICAUX       //
    /////////////////////////////////////////
    if(_onGround==getPosition().y) {
        if(_jump) {
            _onGround=-1;
            newSpeed.y += -jumpAccel;
            _jump = false;
            if (newSpeed.x>0) {
                if (_state != JUMPING_RIGHT) {
                    _state = JUMPING_RIGHT;
                    setAnimation(JUMPING_RIGHT);
                }
            } else if (newSpeed.x<0) {
                if (_state != JUMPING_LEFT) {
                    _state = JUMPING_LEFT;
                    setAnimation(JUMPING_LEFT);
                }
            } else if (_state == STANDING_RIGHT) {
                _state = JUMPING_RIGHT;
                setAnimation(JUMPING_RIGHT);
            } else {
                _state = JUMPING_LEFT;
                setAnimation(JUMPING_LEFT);
            }
        }
    } else {
        _onGround = -1;
    }
    setSpeed(newSpeed);
	AnimatedSprite::update(seconds);
    if (_camera) {
        Vector2d camPos = _camera->getCameraPosition();
        //camPos.x += seconds*50;
        Vector2d camSize = _camera->getCameraSize();
        if ( getAbsolutePosition().x < camSize.x/10.) {
            camPos.x += getAbsolutePosition().x - camSize.x/10.;
        } else if ( getAbsolutePosition().x + getAbsoluteSize().x > camSize.x*9./10.) {
            camPos.x += getAbsolutePosition().x + getAbsoluteSize().x - camSize.x*9./10.;
        }
        if ( getAbsolutePosition().y < camSize.y/10.) {
            camPos.y += getAbsolutePosition().y - camSize.y/10.;
        } else if ( getAbsolutePosition().y + getAbsoluteSize().y > camSize.y*9./10.) {
            camPos.y += getAbsolutePosition().y + getAbsoluteSize().y - camSize.y*9./10.;
        }
        _camera->setCameraPosition(camPos);
    }
    return 0;
}

int PersoTest::draw()
{
    AnimatedSprite::draw();

    return 0;
}

void PersoTest::mouseMoved(Vector2d pos)
{
	_mousePos = pos;
}

void PersoTest::keyPressed(Key::Key key)
{
	if (key == Key::A) {
		_trust = 1;
	} else if (key == Key::Left) {
	    _movingLeft= true;
	} else if (key == Key::Right) {
        _movingRight= true;
	} else if (key == Key::Up) {
	    if (_onGround==getPosition().y) {
	        _jump = true;
	    }
	} else if (key == Key::S) {
	    // Switch collision layer
	    Moteur2D::getInstance()->getCurrentScreen()->deleteCollider(0, getCollider());
	    Moteur2D::getInstance()->getCurrentScreen()->addCollider(1, getCollider());
	}
}
void PersoTest::keyReleased(Key::Key key)
{

	if (key == Key::A) {
		_trust = 0;
	} else if (key == Key::Left) {
        _movingLeft= false;
	} else if (key == Key::Right) {
        _movingRight= false;
	} else if (key == Key::Up) {
	    _jump = false;
	}
}

void PersoTest::handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int ...)
{
    Vector2d oldPos = getPosition() - (getSpeed()*secsSinceLastFrame);
    Vector2d oldPosColided = weColided->getPosition()- (weColided->getSpeed()*secsSinceLastFrame);
    double diffLR = oldPos.x - (oldPosColided.x+weColided->getRelativeSize().x);
    double diffRL = oldPos.x+getRelativeSize().x - oldPosColided.x;
    double diffTB = oldPos.y - (oldPosColided.y+weColided->getRelativeSize().y);
    double diffBT = oldPos.y+getRelativeSize().y - oldPosColided.y;

    Vector2d newPos = getPosition();
    Vector2d newSpeed = getSpeed();
    if (diffRL <= 0 && diffRL < diffBT && diffRL < -diffTB) {
        // Collision on Right of Perso
        newSpeed.x = 0;
        newPos.x = weColided->getPosition().x-getRelativeSize().x;
        if (_onGround==newPos.y && _state != STANDING_RIGHT) {
            _state = STANDING_RIGHT;
            setAnimation(STANDING_RIGHT);
        }

    } else if (diffLR >= 0 && diffLR > -diffBT && diffLR > diffTB) {
        // Collision on Left of Perso
        newSpeed.x = 0;
        newPos.x = weColided->getPosition().x+weColided->getRelativeSize().x;
        if (_onGround==newPos.y && _state != STANDING_LEFT) {
            _state = STANDING_LEFT;
            setAnimation(STANDING_LEFT);
        }
    } else if (diffBT <= -diffTB) {
        // Collision on Bottom of Perso
        newSpeed.y = 0;
        newPos.y = weColided->getPosition().y-getRelativeSize().y;
        _onGround = newPos.y;
        if (newSpeed.x==0) {
            if (_state == STANDING_RIGHT || _state == JUMPING_RIGHT) {
                _state = STANDING_RIGHT;
                setAnimation(STANDING_RIGHT);
            } else if (_state == STANDING_LEFT || _state == JUMPING_LEFT) {
                _state = STANDING_LEFT;
                setAnimation(STANDING_LEFT);
            }
        }
    } else {
        // Collision on top of Perso
        newSpeed.y = 0;
        newPos.y = weColided->getPosition().y+weColided->getRelativeSize().y;
    }
    setPosition(newPos);
    setSpeed(newSpeed);


}

void PersoTest::setCamera(Camera *camera)
{
    _camera = camera;
}














