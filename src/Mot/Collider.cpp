
#include "Collider.h"
#include "WorldElement.h"

Collider::Collider(WorldElement *we) : _colliderType(NONE), _we (we), _deltaX(0), _deltaY(0), _compo1(0), _compo2(0), _compo3(0)
{
    // TODO Auto-generated constructor stub

}

Collider::~Collider()
{
    // TODO Auto-generated destructor stub
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
    std::cout << "Youpi : Collider::detectCollisionWith" << std::endl;
    switch (_colliderType) {
        case COLLIDER_RECTANGULAR:
            switch (collider->_colliderType) {
                case COLLIDER_RECTANGULAR:
                    detectRectOnRect(this, collider);
                    break;
                case COLLIDER_CIRCULAR:
                    detectRectOnCirc(this, collider);
                    break;
            }
            break;
        case COLLIDER_CIRCULAR:
            switch (collider->_colliderType) {
                case COLLIDER_RECTANGULAR:
                    detectRectOnCirc(collider, this);
                    break;
                case COLLIDER_CIRCULAR:
                    detectCircOnCirc(this, collider);
                    break;
            }
            break;
    }
}

void Collider::detectRectOnRect (Collider * collider1, Collider * collider2)
{
    double col1X = collider1->_we->getPosition().x + collider1->_deltaX;
    double col1Y = collider1->_we->getPosition().y + collider1->_deltaY;
    double col1W = collider1->_compo1;
    double col1H = collider1->_compo2;

    double col2X = collider2->_we->getPosition().x + collider2->_deltaX;
    double col2Y = collider2->_we->getPosition().y + collider2->_deltaY;
    double col2W = collider2->_compo1;
    double col2H = collider2->_compo2;

    std::cout << "Youpi : Collider::detectRectOnRect" << std::endl;
    if (!(col2X > col1X+col1W || col2Y > col1Y+col1H || col2X+col2W < col1X || col2Y+col2H < col1Y)) {
        std::cout << "Youpi : COLLISION" << std::endl;
        collider1->_we->handleCollisionWith(collider2->_we, 0);
        collider2->_we->handleCollisionWith(collider1->_we, 0);
    }
}
void Collider::detectRectOnCirc (Collider * colliderRect, Collider * colliderCirc)
{

}
void Collider::detectCircOnCirc (Collider * collider1, Collider * collider2)
{

}




