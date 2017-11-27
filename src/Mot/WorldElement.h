
#ifndef SRC_MOT_WORLDELEMENTS_H_
#define SRC_MOT_WORLDELEMENTS_H_

#include "Vector2d.h"

#ifdef IN_QT
#include <QGraphicsScene>

#else

#endif
#include <iostream>
class Collider;
class WorldElement {

protected:
    Vector2d _pos;
    Vector2d _speed;
    Vector2d _accel;
    Vector2d _size;

    Collider * _collider;
    double _scale;
    Vector2d _absolutePos;
    Vector2d _absoluteSize;
    Vector2d _relativeSize;
    double _absoluteScale;

public:
    WorldElement();
    virtual ~WorldElement();

    int baseUpdate(double seconds);
    int baseDraw(Vector2d pos = Vector2d(), double scale = 1);

    Vector2d getPosition();
    Vector2d getSpeed();
    Vector2d getAcceleration();
    Vector2d getSize();

    Vector2d getAbsolutePosition();
    Vector2d getAbsoluteSize();
    Vector2d getRelativeSize();

    void setPosition(Vector2d pos);
    void setSpeed(Vector2d speed);
    void setAcceleration(Vector2d accel);
    void setSize(Vector2d size);

    void movePosition(Vector2d deltaPos);
    void moveSpeed(Vector2d deltaSpeed);
    void moveAcceleration(Vector2d deltaAccel);

    virtual void handleCollisionWith(WorldElement * weColided, double timeSinceLastFrame, int nbAdditionnalInfo...){}
    Collider* getCollider();
    void setCollider(Collider* collider);

    virtual double getScale();
    virtual double getAbsoluteScale();
    virtual void setScale(double scale);

    // Specifics Functions
#ifdef IN_QT
    virtual void addedInScene(QGraphicsScene * scene){}

#else

#endif

protected:
    virtual int update(double seconds){return 0;}
    virtual int draw(Vector2d pos = Vector2d(), double scale = 1);

};

#endif /* SRC_MOT_WORLDELEMENTS_H_ */
