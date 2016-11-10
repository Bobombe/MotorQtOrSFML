
#include "WorldElement.h"

WorldElement::WorldElement()
{

}

WorldElement::~WorldElement()
{
}

int WorldElement::baseUpdate(double seconds)
{
	int retVal = update(seconds);
    _speed += _accel*seconds;
    _pos += _speed*seconds;
    return retVal;
}
int WorldElement::baseDraw(Vector2d pos)
{
	int retVal = draw(pos);
	_accel.toNull();
    return 0;
}


Vector2d WorldElement::getPosition()
{
    return _pos;
}
Vector2d WorldElement::getSpeed()
{
    return _speed;
}
Vector2d WorldElement::getAcceleration()
{
    return _accel;
}

void WorldElement::setPosition(Vector2d pos)
{
    _pos = pos;
}
void WorldElement::setSpeed(Vector2d speed)
{
    _speed = speed;
}
void WorldElement::setAcceleration(Vector2d accel)
{
    _accel = accel;
}


void WorldElement::movePosition(Vector2d deltaPos)
{
    _pos += deltaPos;
}
void WorldElement::moveSpeed(Vector2d deltaSpeed)
{
    _speed += deltaSpeed;
}
void WorldElement::moveAcceleration(Vector2d deltaAccel)
{
    _accel += deltaAccel;
}
