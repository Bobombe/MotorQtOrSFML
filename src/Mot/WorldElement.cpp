
#include "WorldElement.h"

WorldElement::WorldElement() : _collider(0), _scale(1), _absoluteScale(1)
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
int WorldElement::baseDraw(Vector2d pos, double scale)
{
	int retVal = draw(pos, scale);
	_accel.toNull();
    return retVal;
}


Vector2d WorldElement::getPosition()
{
    return _pos;
}
Vector2d WorldElement::getAbsolutePosition()
{
    return _absolutePos;
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
Vector2d WorldElement::getAbsoluteSize()
{
    return _absoluteSize;
}
Vector2d WorldElement::getRelativeSize()
{
    return _relativeSize;
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


double WorldElement::getScale()
{
    return _scale;
}
double WorldElement::getAbsoluteScale()
{
    return _absoluteScale;
}
void WorldElement::setScale(double scale)
{
    if (scale != _scale) {
        _scale = scale;
    }
}

int WorldElement::draw(Vector2d pos, double scale)
{
    _absolutePos = pos + _pos*scale;
    _absoluteScale = scale * _scale;
    _absoluteSize = _size * _absoluteScale;
    _relativeSize = _size * _scale;
    return 0;
}













