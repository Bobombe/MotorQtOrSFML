#include "Screen.h"
#include <iostream>
#include "moteur2d.h"

Screen::Screen()
{
#ifdef IN_QT
    QGraphicsView * view = Moteur2D::getInstance()->getView();
    _scene = new QGraphicsScene(view);
    view->setScene(_scene);
    _scene->setSceneRect(0, 0, view->geometry().width(), view->geometry().height());

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
}

int Screen::update(double seconds)
{
    for (unsigned int i = 0; i < _forces.size(); i++)
    {
    	_forces[i]->apply();
    }
    for (unsigned int i = 0; i < _worldElements.size(); i++)
    {
        _worldElements[i]->baseUpdate(seconds);
    }
    // Handle collisions
    for (std::map<int, std::vector<Collider*> >::iterator it=_collisionLayers.begin(); it!=_collisionLayers.end(); ++it)
    {
        std::vector<Collider*> colliders = it->second;
        for (unsigned int i = 0; i < colliders.size()-1; i++)
        {
            for (unsigned int j = i+1; j < colliders.size(); j++)
            {
                colliders[i]->detectCollisionWith(colliders[j], seconds);
            }
        }
    }
    return 0;
}

int Screen::draw(Vector2d pos)
{
    for (unsigned int i = 0; i < _worldElements.size(); i++)
    {
        _worldElements[i]->baseDraw(pos + _pos);
    }
    return 0;
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
    _collisionLayers[layer].push_back(c);
}

void Screen::deleteCollider(int layer, Collider* c)
{
    std::vector<Collider*> colliders = _collisionLayers[layer];
    for (int i = 0; i<colliders.size(); i++)
    {
        if (c==colliders[i])
        {
            colliders.erase(colliders.begin()+i);
            return;
        }
    }
}
















