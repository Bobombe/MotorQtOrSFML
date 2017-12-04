
#include "Spaceship.h"
#include "Dephazor.h"
#include "Opponent.h"
#include "Pod.h"
#include "ScreenLevel1.h"
#include "Mot/Vector2d.h"
#include "Mot/Rectangle.h"
#include "Mot/moteur2d.h"

Spaceship::Spaceship() : Sprite("./resLD40/spaceship.png"),
                        _movingLeft(false), _movingRight(false), _movingUp(false), _movingDown(false), _firing(false), _fireCoolDown(0),
                        _invincible(0), _usingEnergy(3), _maxAccel(4000), _maxSpeed(600), _maxPosX(ScreenLevel1::SIZEX-70), _minPosX(10),
                        _minPosY(10), _maxPosY(ScreenLevel1::SIZEY-90), _nbPodDocked(0), _credits(100), _power(100)
{
	setPosition(Vector2d(420, 900));

    _collider =  new Collider(this);
    _collider->initRectangular(0, 0, getSize().x, getSize().y-10);

    // Prepare Docks
    _dockPositions.push_back(Vector2d(-15, -5));
    _dockPositions.push_back(Vector2d(55, -5));
    _dockPositions.push_back(Vector2d(-16, 35));
    _dockPositions.push_back(Vector2d(56, 35));
    _dockPositions.push_back(Vector2d(-35, -5));
    _dockPositions.push_back(Vector2d(75, -5));
    _dockPositions.push_back(Vector2d(-36, 35));
    _dockPositions.push_back(Vector2d(76, 35));
    _dockPositions.push_back(Vector2d(-55, -5));
    _dockPositions.push_back(Vector2d(95, -5));
    _dockPositions.push_back(Vector2d(-56, 35));
    _dockPositions.push_back(Vector2d(96, 35));
    _dockPositions.push_back(Vector2d(20, 66));
    for (unsigned int i = 0; i < _dockPositions.size(); i++) {
        _docks.push_back(0);
    }
}

Spaceship::~Spaceship()
{
}


int Spaceship::update(double seconds)
{
    if (_fireCoolDown > 0) {
        _fireCoolDown-= seconds;
    }
    if (_invincible > 0) {
        _invincible-= seconds;
    }
    _usingEnergy-=seconds;
    if (_usingEnergy<0) {
        _usingEnergy = -0.27*_nbPodDocked+4;
        _power-=1;
    }

    /////////////////////////////////////////
   //       DEPLACEMENTS HORIZONTAUX      //
  /////////////////////////////////////////
    Vector2d newSpeed = getSpeed();
    if (_movingRight && !_movingLeft) {
        newSpeed.x+=_maxAccel*seconds;
        if (newSpeed.x>_maxSpeed) {
            newSpeed.x=_maxSpeed;
        }
    } else if (_movingLeft && !_movingRight) {
        newSpeed.x-=_maxAccel*seconds;
        if (newSpeed.x<-_maxSpeed) {
            newSpeed.x=-_maxSpeed;
        }
    } else { // Slowing
        if (newSpeed.x > 0) {
            //m_orienteDroite = true;
            newSpeed.x-=_maxAccel/1.2*seconds;
            if (newSpeed.x<=0) {
                newSpeed.x=0;
            }
        } else if (newSpeed.x < 0) {
            //m_orienteDroite = false;
            newSpeed.x+=_maxAccel/1.2*seconds;
            if (newSpeed.x>=0) {
                newSpeed.x=0;
            }
        }
    }


    /////////////////////////////////////////
   //        DEPLACEMENTS VERTICAUX       //
  /////////////////////////////////////////
    if (_movingDown && !_movingUp) {
        newSpeed.y+=_maxAccel*seconds;
        if (newSpeed.y>_maxSpeed) {
            newSpeed.y=_maxSpeed;
        }
    } else if (_movingUp && !_movingDown) {
        newSpeed.y-=_maxAccel*seconds;
        if (newSpeed.y<-_maxSpeed) {
            newSpeed.y=-_maxSpeed;
        }
    } else { // Slowing
        if (newSpeed.y > 0) {
            //m_orienteDroite = true;
            newSpeed.y-=_maxAccel/1.2*seconds;
            if (newSpeed.y<=0) {
                newSpeed.y=0;
            }
        } else if (newSpeed.y < 0) {
            //m_orienteDroite = false;
            newSpeed.y+=_maxAccel/1.2*seconds;
            if (newSpeed.y>=0) {
                newSpeed.y=0;
            }
        }
    }
    if (_firing && _fireCoolDown<=0) {
        _fireCoolDown = 0.25;
        Dephazor * fire = new Dephazor(_parent);
        fire->setPosition(Vector2d(getPosition().x+15, getPosition().y-10));
    }

    setSpeed(newSpeed);
	Sprite::update(seconds);
	Vector2d pos = getAbsolutePosition();
	Vector2d speed = getSpeed();
	if (pos.x < _minPosX) {
        pos.x = _minPosX;
        speed.x = 0;
	} else if (pos.x>_maxPosX) {
        pos.x = _maxPosX;
        speed.x = 0;
	}
	if (pos.y < _minPosY) {
        pos.y = _minPosY;
        speed.y = 0;
	} else if (pos.y>_maxPosY) {
        pos.y = _maxPosY;
        speed.y = 0;
	}
	setSpeed(speed);
	setPosition(pos);
    return 0;
}

int Spaceship::draw()
{
    Sprite::draw();

    return 0;
}

void Spaceship::mouseMoved(Vector2d pos)
{
}

void Spaceship::keyPressed(Key::Key key)
{
	if (key == Key::Left) {
	    _movingLeft= true;
	} else if (key == Key::Right) {
        _movingRight= true;
	} else if (key == Key::Up) {
	    _movingUp= true;
	} else if (key == Key::Down) {
	    _movingDown= true;
	} else if (key == Key::Space) {
	    _firing= true;
	}
}
void Spaceship::keyReleased(Key::Key key)
{
	if (key == Key::Left) {
	    _movingLeft= false;
	} else if (key == Key::Right) {
        _movingRight= false;
	} else if (key == Key::Up) {
	    _movingUp= false;
	} else if (key == Key::Down) {
	    _movingDown= false;
	} else if (key == Key::Space) {
	    _firing= false;
	}
}

void Spaceship::handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...)
{
    Dephazor * dephazor = dynamic_cast<Dephazor*>(weColided);
    Opponent * opponent = dynamic_cast<Opponent*>(weColided);
    if (dephazor) {

    } else if (opponent) {
        if (_invincible<=0) {
            _power-=20;
            _invincible = 1;
        }
    } else {
        Pod * pod = dynamic_cast<Pod*>(weColided->getParent());
        Planet * planet = dynamic_cast<Planet*>(weColided->getParent());
        if (pod) {
            pod->acceptCall();
        } else if (planet) {
            _credits -= (100-_power);
            _power = 100;
            if (_credits<0) {
                _power+=_credits;
                _credits = 0;
            }
            int lastDocked = 0;
            for (int i = _docks.size()-1; i >= 0 && i > lastDocked - 4; i--) {
                if (_docks[i]) {
                    if (i>7 || i==7 && !_docks[11]
                            || i==6 && !_docks[10]
                            || i==5 && !_docks[9]
                            || i==4 && !_docks[8] && !_docks[12]
                            || i==3 && !_docks[7] && !_docks[11]
                            || i==2 && !_docks[6] && !_docks[10]
                            || i==1 && !_docks[5] && !_docks[9]
                            || i==0 && !_docks[4] && !_docks[8])
                    {
                        int reward = _docks[i]->undock(planet);
                        if (reward>=0) {
                            _docks[i] = 0;
                            _nbPodDocked--;
                            _credits+=reward;
                            updateMovements();
                        } else {
                            if (lastDocked == 0 && i != _docks.size()-1){
                                lastDocked = i;
                            }
                        }
                    }
                }

            } // end for
            planet->freeBlock();
        }
    }


}

bool Spaceship::getDockPosition(Pod * dockingPod, Vector2d& dockPosition)
{
    bool found = false;
    for (unsigned int i = 0; !found && i < _docks.size(); i++) {
        if (!_docks[i]) {
            found = true;
            dockPosition = _dockPositions[i];
            _docks[i] = dockingPod;
            _nbPodDocked++;
            updateMovements();
        }
    }
    return found;
}

void Spaceship::updateMovements()
{
    if (_docks[8] || _docks[10]) {
        _minPosX = 10 + 3*20;
    } else if (_docks[4] || _docks[6]) {
        _minPosX = 10 + 2*20;
    } else if (_docks[0] || _docks[2]) {
        _minPosX = 10 + 20;
    } else {
        _minPosX = 10;
    }
    if (_docks[9] || _docks[11]) {
        _maxPosX = ScreenLevel1::SIZEX - 70 - 3*20;
    } else if (_docks[5] || _docks[7]) {
        _maxPosX = ScreenLevel1::SIZEX - 70 - 2*20;
    } else if (_docks[1] || _docks[3]) {
        _maxPosX = ScreenLevel1::SIZEX - 70 - 20;
    } else {
        _maxPosX = ScreenLevel1::SIZEX - 70;
    }

    double emptySpeed = 800;
    double fullSpeed = 150;
    double emptyAccel = 5000;
    double fullAccel = 200;
    _maxSpeed = 2.8*(_nbPodDocked-15)*(_nbPodDocked-15)+190;//emptySpeed - _nbPodDocked*(emptySpeed-fullSpeed)/13.;
    _maxAccel = 21.7*(_nbPodDocked-15)*(_nbPodDocked-15)+115;//emptyAccel - _nbPodDocked*(emptyAccel-fullAccel)/13.;
}

void Spaceship::getStats(int& credits, int& power, std::vector<PassengerStats>& passengersHappiness)
{
    credits = _credits;
    power = _power;
}












