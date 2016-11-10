
#include "PersoTest.h"
#include "Mot/Vector2d.h"

PersoTest::PersoTest() : Sprite ("./Ressources/Fond3.png", Vector2d(15, 30), Vector2d(15, 30))
{
	_pos.x = 100;
	_pos.y = 400;
	_mousePos = _pos;
	_trust = 0;
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
