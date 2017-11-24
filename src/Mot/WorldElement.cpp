
#include "WorldElement.h"

WorldElement::WorldElement() : _collider(0), _scale(1)
{

}

WorldElement::~WorldElement()
{
    if (_collider) {
        delete _collider;
    }
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
    return retVal;
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
Vector2d WorldElement::getSize()
{
    return _size;
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
void WorldElement::setSize(Vector2d size)
{
    _size = size;
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

Collider* WorldElement::getCollider()
{
    return _collider;
}
void WorldElement::setCollider(Collider* collider)
{
    _collider = collider;
}


float WorldElement::getScale()
{
    return _scale;
}
void WorldElement::setScale(float scale)
{
    if (scale != _scale) {
        _scale = scale;
    }
}
