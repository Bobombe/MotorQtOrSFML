
#ifndef SRC_MOT_WORLDELEMENTS_H_
#define SRC_MOT_WORLDELEMENTS_H_

#include "Vector2d.h"

#ifdef IN_QT
#include <QGraphicsScene>

#else

#endif
#include <iostream>
#include <string>
#include <vector>
#include <map>
class Collider;
class WorldElement {

private:
    Vector2d _pos;                  //// Position relative to parent WorldElement
    Vector2d _speed;
    Vector2d _accel;
    Vector2d _size;                 //// Original size (without scaling)

    double _scale;                  //// Original scale of this WE (without parent scale

    Vector2d _absolutePos;          //// Absolute position top left app corner being ref.
    Vector2d _relativeSize;         //// Size relative to parent (= _size*_scale)
    Vector2d _absoluteSize;         //// Real size after scaling from parent scale and this object scale)
    double _absoluteScale;          //// = _scale*_parent->_absoluteScale

protected:

    Collider * _collider;

    WorldElement * _parent;
    std::map<int, std::vector<WorldElement *> > _children;
    int _layer;
    std::string _weName;

#ifdef IN_QT
    QGraphicsScene * _scene;

#else

#endif

public:

    WorldElement();
    WorldElement(WorldElement * parent, int layer = 0);
    virtual ~WorldElement();

    int baseUpdate(double seconds);
    int baseDraw();

    /////////////////////////////////////////////////
    // GETTER OF BASED CHARACTERISTIQUES
    /////////////////////////////////////////////////
    Vector2d getPosition();
    Vector2d getSpeed();
    Vector2d getAcceleration();
    Vector2d getSize();
    virtual double getScale();


    /////////////////////////////////////////////////
    // GETTER OF DERIVATIVE FROM CHARACTERISTIQUES
    /////////////////////////////////////////////////
    Vector2d getAbsolutePosition();
    Vector2d getRelativeSize();
    Vector2d getAbsoluteSize();
    virtual double getAbsoluteScale();

    /////////////////////////////////////////////////
    // SETTER OF BASED CHARACTERISTICS
    /////////////////////////////////////////////////
    virtual void setPosition(Vector2d pos);
    void setSpeed(Vector2d speed);
    void setAcceleration(Vector2d accel);
    void setSize(Vector2d size);
    virtual void setScale(double scale);
    void updateCharacteristics();

    /////////////////////////////////////////////////
    // MOVER OF BASED CHARACTERISTIQUES
    /////////////////////////////////////////////////
    void movePosition(Vector2d deltaPos);
    void moveSpeed(Vector2d deltaSpeed);
    void moveAcceleration(Vector2d deltaAccel);

    /////////////////////////////////////////////////
    // HANDLE COLLIDER
    /////////////////////////////////////////////////
    virtual void handleCollisionWith(WorldElement * weColided, double timeSinceLastFrame, int nbAdditionnalInfo...){}
    Collider* getCollider();
    void setCollider(Collider* collider);


    WorldElement * getParent();
    void setParent(WorldElement * parent, int layer = 0);

protected:
    virtual int update(double seconds);
    virtual int draw();

    // Specifics Functions
#ifdef IN_QT
    void updateScene();
    void setScene(QGraphicsScene * scene);
    virtual void updateScene(QGraphicsScene * scene);

#else

#endif

};

#endif /* SRC_MOT_WORLDELEMENTS_H_ */
