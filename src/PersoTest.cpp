
#include "PersoTest.h"
#include "Mot/Vector2d.h"
#include "Mot/Rectangle.h"

PersoTest::PersoTest() : AnimatedSprite("./Ressources/Perso.PNG")
{
	_pos.x = 100;
	_pos.y = 200;
	_mousePos = _pos;
	_trust = 0;
	// 0 : Stand still
	addSubRect(0, Rectangle(0, 60, 40, 60));
	setFramePerSecs(0, 1);
	// 1 : run right
    addSubRect(1, Rectangle(40, 60, 40, 60));
    addSubRect(1, Rectangle(80, 60, 40, 60));
    addSubRect(1, Rectangle(120, 60, 40, 60));
    addSubRect(1, Rectangle(160, 60, 40, 60));
    addSubRect(1, Rectangle(200, 60, 40, 60));
    addSubRect(1, Rectangle(240, 60, 40, 60));
	setFramePerSecs(1, 12);
    // 2 : Jump right
    addSubRect(2, Rectangle(280, 60, 40, 60));
	setFramePerSecs(2, 1);
    // 3 : Stand still Left
    addSubRect(3, Rectangle(360, 0, 40, 60));
    setFramePerSecs(3, 1);
    // 4 : run left
    addSubRect(4, Rectangle(120, 0, 40, 60));
    addSubRect(4, Rectangle(160, 0, 40, 60));
    addSubRect(4, Rectangle(200, 0, 40, 60));
    addSubRect(4, Rectangle(240, 0, 40, 60));
    addSubRect(4, Rectangle(280, 0, 40, 60));
    addSubRect(4, Rectangle(320, 0, 40, 60));
    setFramePerSecs(4, 6);
    // 2 : Jump left
    addSubRect(5, Rectangle(80, 0, 40, 60));
    setFramePerSecs(5, 1);
}

PersoTest::~PersoTest()
{
}


int PersoTest::update(double seconds)
{
	double fixedThrust = 100;
	if (_trust) {
		_trust+= fixedThrust*seconds;
		Vector2d accelTrust = (_mousePos-_pos);
		accelTrust.normalize();
		accelTrust*=_trust;
		_accel += accelTrust;
		std::cout << "Youpi : _trust = " << _trust << "_mousePos = ("  << _mousePos.x << " ; " << _mousePos.y << std::endl;
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
	} else if (key == Key::Down) {
		setAnimation(0);
		_speed.y += 100;
	} else if (key == Key::Left) {
		setAnimation(4);
		_speed.x += -100;
	} else if (key == Key::Right) {
		setAnimation(1);
		_speed.x += 100;
	} else if (key == Key::Up) {
		setAnimation(2);
		_speed.y += -1000;
	}
}
void PersoTest::keyReleased(Key::Key key)
{

	if (key == Key::A) {
		_trust = 0;
        setAnimation(0);
	} else if (key == Key::Down) {
		_speed.y += -100;
        setAnimation(0);
	} else if (key == Key::Left) {
		_speed.x += 100;
        setAnimation(0);
	} else if (key == Key::Right) {
		_speed.x += -100;
        setAnimation(0);
	} else if (key == Key::Up) {
		_speed.y += 1000;
        setAnimation(0);
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
        // Collision on Left
        _speed.x = 0;
        _pos.x = weColided->getPosition().x-_size.x;
        std::cout << "Youpi : Collision on Left" << std::endl;
    } else if (diffLR >= 0 && diffLR > -diffBT && diffLR > diffTB) {
        // Collision on Right
        _speed.x = 0;
        _pos.x = weColided->getPosition().x+weColided->getSize().x;
        std::cout << "Youpi : Collision on Right" << std::endl;
        std::cout << "Youpi : diff = " << diffLR << " , " << diffRL << " ; " << diffTB << " , " << diffBT << std::endl;
    } else if (diffBT <= 0) {
        // Collision on Top
        _speed.y = 0;
        _pos.y = weColided->getPosition().y-_size.y;
        std::cout << "Youpi : Collision on Top" << std::endl;
    } else {
        // Collision on Bottom
        _speed.y = 0;
        _pos.y = weColided->getPosition().y+weColided->getSize().y;
        std::cout << "Youpi : Collision on Bottom" << std::endl;
    }


}














