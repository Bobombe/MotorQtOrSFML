
#include "PersoTest.h"
#include "Mot/Vector2d.h"
#include "Mot/Rectangle.h"
#include "Mot/moteur2d.h"

PersoTest::PersoTest() : AnimatedSprite("./Ressources/Perso.PNG"), _state(STANDING_RIGHT), _movingLeft(false), _movingRight(false), _jump(false), _onGround(-1)
{
	_pos.x = 100;
	_pos.y = 200;
	_mousePos = _pos;
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
		Vector2d accelTrust = (_mousePos-_pos);
		accelTrust.normalize();
		accelTrust*=_trust;
		_accel += accelTrust;
	}
    /////////////////////////////////////////
   //       DEPLACEMENTS HORIZONTAUX      //
  /////////////////////////////////////////
   if (_movingRight && !_movingLeft) {
       _speed.x+=maxAccel*seconds;
       if (_speed.x>maxSpeed) {
           _speed.x=maxSpeed;
       }
       if(_onGround!=_pos.y) {
           if (_state != JUMPING_RIGHT) {
               _state = JUMPING_RIGHT;
               setAnimation(JUMPING_RIGHT);
           }
       } else {
           if (_speed.x < 0) {
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
       _speed.x-=maxAccel*seconds;
       if (_speed.x<-maxSpeed) {
           _speed.x=-maxSpeed;
       }
       if(_onGround!=_pos.y) {
           if (_state != JUMPING_LEFT) {
               _state = JUMPING_LEFT;
               setAnimation(JUMPING_LEFT);
           }
       } else {
           if (_speed.x > 0) {
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
       if (_speed.x > 0) {
           //m_orienteDroite = true;
           _speed.x-=maxAccel/1.2*seconds;
           if (_speed.x<=0) {
               _speed.x=0;
               if (_onGround==_pos.y && _state != STANDING_RIGHT) {
                   _state = STANDING_RIGHT;
                   setAnimation(STANDING_RIGHT);
               }
           } else if (_onGround==_pos.y && _state != STOPPING_RIGHT) {
               _state = STOPPING_RIGHT;
               setAnimation(STOPPING_RIGHT);
           }
       } else if (_speed.x < 0) {
           //m_orienteDroite = false;
           _speed.x+=maxAccel/1.2*seconds;
           if (_speed.x>=0) {
               _speed.x=0;
               if (_onGround==_pos.y && _state != STANDING_LEFT) {
                   _state = STANDING_LEFT;
                   setAnimation(STANDING_LEFT);
               }
           } else if (_onGround==_pos.y && _state != STOPPING_LEFT) {
               _state = STOPPING_LEFT;
               setAnimation(STOPPING_LEFT);
           }
       }
   }
    /////////////////////////////////////////
   //        DEPLACEMENTS VERTICAUX       //
  /////////////////////////////////////////
   if(_onGround==_pos.y) {
       if(_jump) {
           _onGround=-1;
           _speed.y += -jumpAccel;
           if (_speed.x>0) {
               if (_state != JUMPING_RIGHT) {
                   _state = JUMPING_RIGHT;
                   setAnimation(JUMPING_RIGHT);
               }
           } else if (_speed.x<0) {
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
	AnimatedSprite::update(seconds);
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
	    if (_onGround==_pos.y) {
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

void PersoTest::handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...)
{
    Vector2d oldPos = _pos - (_speed*secsSinceLastFrame);
    Vector2d oldPosColided = weColided->getPosition()- (weColided->getSpeed()*secsSinceLastFrame);
    double diffLR = oldPos.x - (oldPosColided.x+weColided->getSize().x);
    double diffRL = oldPos.x+_size.x - oldPosColided.x;
    double diffTB = oldPos.y - (oldPosColided.y+weColided->getSize().y);
    double diffBT = oldPos.y+_size.y - oldPosColided.y;
    if (diffRL <= 0 && diffRL < diffBT && diffRL < -diffTB) {
        // Collision on Right of Perso
        _speed.x = 0;
        _pos.x = weColided->getPosition().x-_size.x;
        if (_onGround==_pos.y && _state != STANDING_RIGHT) {
            _state = STANDING_RIGHT;
            setAnimation(STANDING_RIGHT);
        }

    } else if (diffLR >= 0 && diffLR > -diffBT && diffLR > diffTB) {
        // Collision on Left of Perso
        _speed.x = 0;
        _pos.x = weColided->getPosition().x+weColided->getSize().x;
        if (_onGround==_pos.y && _state != STANDING_LEFT) {
            _state = STANDING_LEFT;
            setAnimation(STANDING_LEFT);
        }
    } else if (diffBT <= 0) {
        // Collision on Bottom of Perso
        _speed.y = 0;
        _pos.y = weColided->getPosition().y-_size.y;
        _onGround = _pos.y;
        if (_speed.x==0) {
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
        _speed.y = 0;
        _pos.y = weColided->getPosition().y+weColided->getSize().y;
    }


}














