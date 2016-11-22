
#include "PersoTest.h"
#include "Mot/Vector2d.h"
#include "Mot/Rectangle.h"

PersoTest::PersoTest() : AnimatedSprite("./Ressources/sprite.png")
{
	_pos.x = 100;
	_pos.y = 400;
	_mousePos = _pos;
	_trust = 0;
	addSubRect(0, Rectangle(0, 0, 64, 64));
	addSubRect(0, Rectangle(64, 0, 64, 64));
	addSubRect(0, Rectangle(128, 0, 64, 64));
	addSubRect(0, Rectangle(192, 0, 64, 64));
	setFramePerSecs(0, 4);
	addSubRect(1, Rectangle(0, 64, 64, 64));
	addSubRect(1, Rectangle(64, 64, 64, 64));
	addSubRect(1, Rectangle(128, 64, 64, 64));
	addSubRect(1, Rectangle(192, 64, 64, 64));
	setFramePerSecs(1, 4);
	addSubRect(2, Rectangle(0, 128, 64, 64));
	addSubRect(2, Rectangle(64, 128, 64, 64));
	addSubRect(2, Rectangle(128, 128, 64, 64));
	addSubRect(2, Rectangle(192, 128, 64, 64));
	setFramePerSecs(2, 4);
	addSubRect(3, Rectangle(0, 192, 64, 64));
	addSubRect(3, Rectangle(64, 192, 64, 64));
	addSubRect(3, Rectangle(128, 192, 64, 64));
	addSubRect(3, Rectangle(192, 192, 64, 64));
	setFramePerSecs(3, 4);
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
	} else if (key == Key::Down) {
		setAnimation(0);
		_speed.y += 100;
	} else if (key == Key::Left) {
		setAnimation(1);
		_speed.x += -100;
	} else if (key == Key::Right) {
		setAnimation(2);
		_speed.x += 100;
	} else if (key == Key::Up) {
		setAnimation(3);
		_speed.y += -100;
	}
}
void PersoTest::keyReleased(Key::Key key)
{

	if (key == Key::A) {
		_trust = 0;
		std::cout << "Youpi : stop thrust" << std::endl;
	} else if (key == Key::Down) {
		_speed.y += -100;
	} else if (key == Key::Left) {
		_speed.x += 100;
	} else if (key == Key::Right) {
		_speed.x += -100;
	} else if (key == Key::Up) {
		_speed.y += 100;
	}
}
