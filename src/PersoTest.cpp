
#include "PersoTest.h"
#include "Mot/Vector2d.h"
#include "Mot/Rectangle.h"

PersoTest::PersoTest() : AnimatedSprite("./Ressources/Fond3.png")
{
	_pos.x = 100;
	_pos.y = 400;
	_mousePos = _pos;
	_trust = 0;
	addSubRect(0, Rectangle(30, 30, 15, 30));
	addSubRect(0, Rectangle(45, 60, 15, 30));
	addSubRect(0, Rectangle(60, 90, 15, 30));
	addSubRect(0, Rectangle(75, 30, 15, 30));
	setFramePerSecs(0, 4);
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
		std::cout << "Youpi : init thrust" << std::endl;
		_trust = 1;
	}
}
void PersoTest::keyReleased(Key::Key key)
{

	if (key == Key::A) {
		_trust = 0;
		std::cout << "Youpi : stop thrust" << std::endl;
	}
}
