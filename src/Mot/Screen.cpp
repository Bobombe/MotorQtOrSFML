#include "Screen.h"
#include <iostream>
#include "moteur2d.h"

Screen::Screen() : _screenInitialized(false), _camera(0)
{
#ifdef IN_QT
    QWidget * widget = Moteur2D::getInstance()->getView();
    _view = new QGraphicsView(widget);
    widget->layout()->addWidget(_view);
    _scene = new QGraphicsScene(_view);
    _view->setScene(_scene);
    _view->setVisible(false);
    _view->setStyleSheet("border: 0px");
    _scene->setSceneRect(0, 0, widget->geometry().width()-22, widget->geometry().height()-22);

#else

#endif
    //ctor
}

Screen::~Screen()
{
    //dtor
    std::cout << "delete Screen " << this << std::endl;
    for (unsigned int i = 0; i<_worldElements.size(); i++)
    {
        delete _worldElements[i];
    }
    for (unsigned int i = 0; i<_forces.size(); i++)
    {
        delete _forces[i];
    }
    for (std::map<int, std::vector<Collider*>* >::iterator it=_collisionLayers.begin(); it!=_collisionLayers.end(); ++it)
    {
        delete it->second;
    }
    delete _view;

}

int Screen::update(double seconds)
{
    if (!_screenInitialized) {
        _screenInitialized = true;
        draw();
    }
    for (unsigned int i = 0; i < _forces.size(); i++)
    {
    	_forces[i]->apply();
    }
    for (unsigned int i = 0; i < _worldElements.size(); i++)
    {
        _worldElements[i]->baseUpdate(seconds);
    }
    // Handle collisions
    for (std::map<int, std::vector<Collider*>* >::iterator it=_collisionLayers.begin(); it!=_collisionLayers.end(); ++it)
    {
        std::vector<Collider*>* colliders = it->second;
        for (unsigned int i = 0; i < colliders->size()-1; i++)
        {
            for (unsigned int j = i+1; j < colliders->size(); j++)
            {
                colliders->at(i)->detectCollisionWith(colliders->at(j), seconds);
            }
        }
    }
    return 0;
}

int Screen::draw(Vector2d pos, double scale)
{
    if (_camera) {
        _pos = -_camera->getCameraPosition();
        _scale = _camera->getCameraScale();
    }
    for (unsigned int i = 0; i < _worldElements.size(); i++)
    {
        _worldElements[i]->baseDraw(pos + _pos*scale, scale*_scale);
    }
    return WorldElement::draw(pos, scale);
}

// Fonctions d'ajouts
void Screen::addWorldElement(WorldElement * we)
{
    _worldElements.push_back(we);
#ifdef IN_QT
    we->addedInScene(_scene);
#else

#endif
}

void Screen::deleteWorldElement(WorldElement * we)
{
    for (int i = 0; i<_worldElements.size(); i++)
    {
        if (we==_worldElements[i])
        {
            _worldElements.erase(_worldElements.begin()+i);
            return;
        }
    }
}

void Screen::addForce(Force * f)
{
	_forces.push_back(f);
}

void Screen::deleteForce(Force * f)
{
    for (int i = 0; i<_forces.size(); i++)
    {
        if (f==_forces[i])
        {
        	_forces.erase(_forces.begin()+i);
            return;
        }
    }
}

void Screen::addCollider(int layer, Collider* c)
{
    if (_collisionLayers.find(layer)==_collisionLayers.end()) {
        _collisionLayers[layer] = new std::vector<Collider*>();
    }
    _collisionLayers[layer]->push_back(c);
}

void Screen::deleteCollider(int layer, Collider* c)
{
    if (_collisionLayers.find(layer)!=_collisionLayers.end()) {
        std::vector<Collider*>* colliders = _collisionLayers[layer];
        for (int i = 0; i<colliders->size(); i++)
        {
            if (c==colliders->at(i))
            {
                colliders->erase(colliders->begin()+i);
                return;
            }
        }
    }
}

#ifdef IN_QT
    void Screen::hide()
    {
        _view->setVisible(false);
    }
    void Screen::show()
    {
        _view->setVisible(true);
    }

#else

#endif
















