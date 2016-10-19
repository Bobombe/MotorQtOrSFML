
#ifndef SRC_MOT_WORLDELEMENTS_H_
#define SRC_MOT_WORLDELEMENTS_H_

#include "Vector2d.h"

#ifdef IN_QT
#include <QGraphicsScene>

#else

#endif
#include <iostream>

class WorldElement {

protected:
    Vector2d _pos;
    Vector2d _speed;
    Vector2d _accel;

public:
    WorldElement();
    virtual ~WorldElement();

    virtual int update(double seconds);
    virtual int draw(Vector2d pos = Vector2d());

    Vector2d getPosition();
    Vector2d getSpeed();
    Vector2d getAcceleration();

    void setPosition(Vector2d pos);
    void setSpeed(Vector2d speed);
    void setAcceleration(Vector2d accel);

    void movePosition(Vector2d deltaPos);
    void moveSpeed(Vector2d deltaSpeed);
    void moveAcceleration(Vector2d deltaAccel);

    // Specifics Functions
#ifdef IN_QT
    virtual void addedInScene(QGraphicsScene * scene){}

#else

#endif

};

#endif /* SRC_MOT_WORLDELEMENTS_H_ */
