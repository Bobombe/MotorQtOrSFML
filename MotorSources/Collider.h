
#ifndef SRC_MOT_COLLIDER_H_
#define SRC_MOT_COLLIDER_H_

#include "Vector2d.h"

class WorldElement;
class Collider
{
    enum COLLIDER_TYPE
    {
        NONE,
        COLLIDER_RECTANGULAR,
        COLLIDER_CIRCULAR
    };
protected:
    COLLIDER_TYPE _colliderType;    // define the type/shape of collider.
    WorldElement *_we;               // Element associated with collider
    bool _collisionEnabled{true};

    // Position of Collider is defined from _we position plus these deltas
    double _deltaX;
    double _deltaY;

    // Additional components defining the collider (width and height for rectangular ...)
    double _compo1;
    double _compo2;
    double _compo3;


public:
    Collider(WorldElement *we);
    virtual ~Collider();

    /*
     * Position define top left angle of rectangle.
     */
    void initRectangular(double deltaX, double deltaY, double width, double height);

    /*
     * Position define the coordinate of the center of the circle.
     */
    void initCircular(double deltaX, double deltaY, double radius);

    virtual void detectCollisionWith(Collider * collider, double seconds);
    void detectRectOnRect (Collider * collider1, Collider * collider2, double seconds);
    void detectRectOnCirc (Collider * colliderRect, Collider * colliderCirc, double seconds);
    void detectCircOnCirc (Collider * collider1, Collider * collider2, double seconds);

    void setCollisionEnabled(bool enabled) {_collisionEnabled = enabled;}
    bool getCollisionEnabled() const {return _collisionEnabled;}

    Vector2d getPos();
    Vector2d getSize();
};

#endif
