
#include "WorldElement.h"
#include "Collider.h"

WorldElement::WorldElement():
    _scale(1), _absoluteScale(1),_collider(nullptr), _parent(nullptr), _layer(0), _weName("WorldElement"), _visible(true)
{
#ifdef IN_QT
    _scene = 0;
#else
#endif
}

WorldElement::WorldElement(WorldElement *parent, int layer):
    _scale(1), _absoluteScale(1), _collider(nullptr), _parent(nullptr), _visible(true)
{
#ifdef IN_QT
    _scene = 0;
#else
#endif
    setParent(parent, layer);
}

WorldElement::~WorldElement()
{
    if (_collider) {
        delete _collider;
    }
    // Remove reference in the list of children of this WE parent.
    if (_parent) {
        for (std::map< int, std::vector< WorldElement * > >::iterator it = _parent->_children.begin(); it != _parent->_children.end(); ++it) {
            for (unsigned int i = 0; i < it->second.size(); i++) {
                if (it->second[i] == this) {
                    it->second.erase(it->second.begin() + i);
                }
            }
        }
    }
    // Delete all children
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); i++) {
            delete it->second[i];
        }
    }
}

int WorldElement::baseUpdate(double seconds)
{
    int retVal = update(seconds);
    return retVal;
}
int WorldElement::baseDraw()
{
    int retVal = 0;
    if (_visible) {
        retVal = draw();
    }
    _accel.toNull();
    return retVal;
}

/////////////////////////////////////////////////
// GETTER OF BASED CHARACTERISTIQUES
/////////////////////////////////////////////////
Vector2d WorldElement::getPosition()
{
    return _pos;
}

Vector2d WorldElement::getRefPoint()
{
    return _refPoint;
}

double WorldElement::getRotation()
{
    return _rotation;
}

double WorldElement::getRotationSpeed()
{
    return _rotationSpeed;
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
double WorldElement::getScale()
{
    return _scale;
}

/////////////////////////////////////////////////
// GETTER OF DERIVATIVE FROM CHARACTERISTIQUES
/////////////////////////////////////////////////
Vector2d WorldElement::getAbsolutePosition()
{
    return _absolutePos;
}

double WorldElement::getAbsoluteRotaion()
{
    return _absoluteRotation;
}
Vector2d WorldElement::getRelativeSize()
{
    return _relativeSize;
}
Vector2d WorldElement::getAbsoluteSize()
{
    return _absoluteSize;
}
double WorldElement::getAbsoluteScale()
{
    return _absoluteScale;
}

Rectangle WorldElement::getBoundingBox()
{
    return Rectangle(_topLeftAbsolutePos, _absoluteSize);
}

Rectangle WorldElement::getRealBoundingBox()
{
    return Rectangle(_topLeftAbsolutePos, _absoluteSize);
}

/////////////////////////////////////////////////
// SETTER OF BASED CHARACTERISTIQUES
/////////////////////////////////////////////////
void WorldElement::setPosition(Vector2d pos)
{
    _pos = pos;
    updateCharacteristics();
}

void WorldElement::setPosition(double posx, double posy)
{
    _pos.x = posx;
    _pos.y = posy;
    updateCharacteristics();
}

void WorldElement::setRefPoint(Vector2d point)
{
    Vector2d refDiff = point-_refPoint;
    // Update children pos
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); i++) {
            it->second[i]->parentRefPointChanged(refDiff);
        }
    }

    // Calculate new position
    refDiff.rotateInDegree(_rotation);
    _pos = _pos+refDiff;
    _refPoint = point;

    // Updating absolute values
    updateCharacteristics();
}

void WorldElement::setRefPointCentered()
{
    setRefPoint(_size/2);
}

void WorldElement::setRotation(double rotation)
{
    _rotation = rotation;
    updateCharacteristics();
}

void WorldElement::setRotationSpeed(double rotationSpeed)
{
    _rotationSpeed = rotationSpeed;
}
void WorldElement::setSpeed(Vector2d speed)
{
    _speed = speed;
}

void WorldElement::setSpeed(double sx, double sy)
{
    _speed.x = sx;
    _speed.y = sy;
}
void WorldElement::setAcceleration(Vector2d accel)
{
    _accel = accel;
}
void WorldElement::setSize(Vector2d size)
{
    _size = size;
    // The size doesn't impact children, no use to call updateCharacteristics().
    _relativeSize = _size * _scale;
    _absoluteSize = _size * _absoluteScale;
}
void WorldElement::setScale(double scale)
{
    _scale = scale;
    updateCharacteristics();
}
void WorldElement::updateCharacteristics()
{
    _relativeSize = _size * _scale;
    if (_parent) {
        _absoluteScale = _scale * _parent->_absoluteScale;
        _absoluteRotation = _rotation + _parent->_absoluteRotation;
        // Todo pos, use parent rotation
        Vector2d ratatedPos = _pos;
        ratatedPos.rotateInDegree(_parent->_absoluteRotation);
        _absolutePos = ratatedPos * _parent->_absoluteScale + _parent->_absolutePos;
    } else {
        _absoluteScale = _scale;
        _absoluteRotation = _rotation;
        _absolutePos = _pos;
    }
    _absoluteSize = _size * _absoluteScale;

    Vector2d transformedRefPoint(_refPoint*_absoluteScale);
    transformedRefPoint.rotateInDegree(_absoluteRotation);
    _topLeftAbsolutePos = _absolutePos - transformedRefPoint;

    // Update children
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); i++) {
            it->second[i]->updateCharacteristics();
        }
    }
}

void WorldElement::parentRefPointChanged(const Vector2d &refDiff)
{
    _pos = _pos-refDiff;
}

/////////////////////////////////////////////////
// MOVER OF BASED CHARACTERISTIQUES
/////////////////////////////////////////////////
void WorldElement::movePosition(Vector2d deltaPos)
{
    setPosition(_pos + deltaPos);
}
void WorldElement::moveSpeed(Vector2d deltaSpeed)
{
    _speed += deltaSpeed;
}
void WorldElement::moveAcceleration(Vector2d deltaAccel)
{
    _accel += deltaAccel;
}

/////////////////////////////////////////////////
// HANDLE COLLIDER
/////////////////////////////////////////////////
Collider *WorldElement::getCollider()
{
    return _collider;
}
void WorldElement::setCollider(Collider *collider)
{
    if (_collider) {
        delete _collider;
    }
    _collider = collider;
}

WorldElement *WorldElement::getParent()
{
    return _parent;
}
void WorldElement::setParent(WorldElement *parent, int layer)
{
    // first unset
    std::map< int, std::vector< WorldElement * > >::iterator it;
    if (_parent) {
        for (it = _parent->_children.begin(); it != _parent->_children.end(); ++it) {
            for (unsigned int i = 0; i < it->second.size(); i++) {
                if (it->second[i] == this) {
                    it->second.erase(it->second.begin() + i);
                }
            }
        }
    }
    // Set
    _parent = parent;
    _layer = layer;
    if (_parent) {
        it = _parent->_children.find(layer);
        if (it != _parent->_children.end()) {
            it->second.push_back(this);
        } else {
            _parent->_children[layer] = std::vector< WorldElement * >(1, this);
        }
    }
#ifdef IN_QT
    updateScene();
#else
#endif
    if (_parent) {
        _pos = (_absolutePos - _parent->getAbsolutePosition()) / _parent->getAbsoluteScale();
    } else {
        _pos = _absolutePos;
    }
    updateCharacteristics();
}

bool WorldElement::isVisible()
{
    return _visible;
}
void WorldElement::setVisible(bool visible)
{
    _visible = visible;
}

int WorldElement::update(double seconds)
{
    int ret = 0;
    _speed += _accel * seconds;
    _rotation += _rotationSpeed * seconds;
    movePosition(_speed * seconds);
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); i++) {
            it->second[i]->baseUpdate(seconds);
        }
    }
    return ret;
}
int WorldElement::draw()
{
    int ret = 0;
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (unsigned int i = 0; i < it->second.size(); i++) {
            it->second[i]->baseDraw();
        }
    }
    return ret;
}

#ifdef IN_QT
void WorldElement::updateScene()
{
    QGraphicsScene *scene = 0;
    WorldElement *parent = _parent;
    while (parent && !scene) {
        scene = parent->_scene;
        parent = parent->_parent;
    }
    setScene(scene);
}

void WorldElement::setScene(QGraphicsScene *scene)
{
    updateScene(scene);
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
            it->second[i]->setScene(scene);
        }
    }
}

void WorldElement::updateScene(QGraphicsScene *scene)
{
    _scene = scene;
}

#else

#endif
