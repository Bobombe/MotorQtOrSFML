
#include "WorldElement.h"

WorldElement::WorldElement():
    _collider(0), _scale(1), _absoluteScale(1), _parent(0), _layer(0), _weName("WorldElement")
{
#ifdef IN_QT
    _scene = 0;
#else
#endif
}

WorldElement::WorldElement(WorldElement *parent, int layer):
    _collider(0), _scale(1), _absoluteScale(1), _parent(0)
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
    if (_parent) {

        for (std::map< int, std::vector< WorldElement * > >::iterator it = _parent->_children.begin(); it != _parent->_children.end(); ++it) {
            for (int i = 0; i < it->second.size(); i++) {
                if (it->second[i] == this) {
                    it->second.erase(it->second.begin() + i);
                }
            }
        }
    }
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
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
    int retVal = draw();
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

/////////////////////////////////////////////////
// SETTER OF BASED CHARACTERISTIQUES
/////////////////////////////////////////////////
void WorldElement::setPosition(Vector2d pos)
{
    _pos = pos;
    if (_parent) {
        _absolutePos = _pos * _parent->_absoluteScale + _parent->_absolutePos;
    } else {
        _absolutePos = _pos;
    }
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
            it->second[i]->setPosition(it->second[i]->getPosition());
        }
    }
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
    _relativeSize = _size * _scale;
    _absoluteSize = _size * _absoluteScale;
}
void WorldElement::setScale(double scale)
{
    _scale = scale;
    _relativeSize = _size * _scale;
    _absoluteSize = _size * _absoluteScale;
    if (_parent) {
        _absoluteScale = _scale * _parent->_absoluteScale;
    } else {
        _absoluteScale = _scale;
    }
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
            it->second[i]->updateCharacteristics();
        }
    }
}
void WorldElement::updateCharacteristics()
{
    _relativeSize = _size * _scale;
    _absoluteSize = _size * _absoluteScale;

    if (_parent) {
        _absoluteScale = _scale * _parent->_absoluteScale;
        _absolutePos = _pos * _parent->_absoluteScale + _parent->_absolutePos;
    } else {
        _absoluteScale = _scale;
        _absolutePos = _pos;
    }
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
            it->second[i]->updateCharacteristics();
        }
    }
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
            for (int i = 0; i < it->second.size(); i++) {
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
    _pos = (_absolutePos - _parent->getAbsolutePosition()) / _parent->getAbsoluteScale();
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
    movePosition(_speed * seconds);
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
            it->second[i]->baseUpdate(seconds);
        }
    }
    return ret;
}
int WorldElement::draw()
{
    int ret = 0;
    for (std::map< int, std::vector< WorldElement * > >::iterator it = _children.begin(); it != _children.end(); ++it) {
        for (int i = 0; i < it->second.size(); i++) {
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
