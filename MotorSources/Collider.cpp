
#include "Collider.h"
#include "WorldElement.h"

Collider::Collider(WorldElement *we) : _colliderType(NONE), _we (we), _deltaX(0), _deltaY(0), _compo1(0), _compo2(0), _compo3(0)
{

}

Collider::~Collider()
{
}


void Collider::initRectangular(double deltaX, double deltaY, double width, double height)
{
    _colliderType = COLLIDER_RECTANGULAR;
    _deltaX = deltaX;
    _deltaY = deltaY;
    _compo1 = width;
    _compo2 = height;
}
void Collider::initCircular(double deltaX, double deltaY, double radius)
{
    _colliderType = COLLIDER_CIRCULAR;
    _deltaX = deltaX;
    _deltaY = deltaY;
    _compo1 = radius;
}

void Collider::detectCollisionWith(Collider * collider, double seconds)
{
    if (_collisionEnabled && collider->_collisionEnabled) {
        switch (_colliderType) {
            case COLLIDER_RECTANGULAR:
                switch (collider->_colliderType) {
                    case COLLIDER_RECTANGULAR:
                        detectRectOnRect(this, collider, seconds);
                        break;
                    case COLLIDER_CIRCULAR:
                        detectRectOnCirc(this, collider, seconds);
                        break;
                    default:
                        break;
                }
                break;
            case COLLIDER_CIRCULAR:
                switch (collider->_colliderType) {
                    case COLLIDER_RECTANGULAR:
                        detectRectOnCirc(collider, this, seconds);
                        break;
                    case COLLIDER_CIRCULAR:
                        detectCircOnCirc(this, collider, seconds);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Collider::detectRectOnRect (Collider * collider1, Collider * collider2, double seconds)
{
    double scale1 = collider1->_we->getScale();
    double scale2 = collider2->_we->getScale();

    double col1X = collider1->_we->getAbsolutePosition().x + collider1->_deltaX*scale1;
    double col1Y = collider1->_we->getAbsolutePosition().y + collider1->_deltaY*scale1;
    double col1W = collider1->_compo1*scale1;
    double col1H = collider1->_compo2*scale1;

    double col2X = collider2->_we->getAbsolutePosition().x + collider2->_deltaX*scale2;
    double col2Y = collider2->_we->getAbsolutePosition().y + collider2->_deltaY*scale2;
    double col2W = collider2->_compo1*scale2;
    double col2H = collider2->_compo2*scale2;

    if (!(col2X > col1X+col1W || col2Y > col1Y+col1H || col2X+col2W < col1X || col2Y+col2H < col1Y)) {
        collider1->_we->handleCollisionWith(collider2->_we, seconds, 0);
        collider2->_we->handleCollisionWith(collider1->_we, seconds, 0);
    }
}
void Collider::detectRectOnCirc (Collider *, Collider *, double)
{

}
void Collider::detectCircOnCirc (Collider *, Collider *, double)
{

}


Vector2d Collider::getPos()
{
    Vector2d res;
    switch (_colliderType) {
        case COLLIDER_RECTANGULAR:
            res = _we->getAbsolutePosition();
            res.x+=_deltaX;
            res.y+=_deltaY;
        break;
        default:
        break;
    }
    return res;
}
Vector2d Collider::getSize()
{
    Vector2d res;
    switch (_colliderType) {
        case COLLIDER_RECTANGULAR:
            res.x = _compo1*_we->getAbsoluteScale();
            res.y = _compo2*_we->getAbsoluteScale();
        break;
        default:
        break;
    }
    return res;
}


