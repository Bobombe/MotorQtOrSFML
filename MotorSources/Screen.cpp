#include "Screen.h"
#include <iostream>
#include "moteur2d.h"
#include "Camera.h"

Screen::Screen(Camera *camera) : WorldElement(), _camera(camera), _screenInitialized(false)//, _weName("Screen")
{
#ifdef IN_QT
    QWidget * widget = Moteur2D::getInstance()->getView();
    _view = new QGraphicsView(widget);
    widget->layout()->addWidget(_view);
    setScene(new QGraphicsScene(_view));
    _view->setScene(_scene);
    _view->setVisible(false);
    _view->setStyleSheet("border: 0px");
    _scene->setSceneRect(0, 0, widget->geometry().width()-22, widget->geometry().height()-22);

#else

#endif
    //ctor
    setSize(Moteur2D::getInstance()->getScreenSize());
    _weName = "Screen";
}

Screen::~Screen()
{
    //dtor
    for (unsigned int i = 0; i<_forces.size(); i++)
    {
        delete _forces[i];
    }
    for (std::map<int, std::vector<Collider*>* >::iterator it=_collisionLayers.begin(); it!=_collisionLayers.end(); ++it)
    {
        delete it->second;
    }
#ifdef IN_QT
    setScene(0);
    delete _view;
#else

#endif

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
    // Update children
    WorldElement::update(seconds);
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
    if (_camera) {
        _camera->baseUpdate(seconds);
        if (_camera->getAbsolutePosition().getNorm() > 0.0001) {
            Vector2d newPos = -_camera->getAbsolutePosition();
            movePosition(newPos);
        }
        if (_camera->getCameraScale() != getScale()) {
            setScale(_camera->getCameraScale());
        }
        _camera->setPosition(0, 0);
    }
    return 0;
}

int Screen::draw()
{
    if (_camera) {
        _camera->baseDraw();
    }
    int ret = WorldElement::draw();
    return ret;
}

void Screen::addForce(Force * f)
{
	_forces.push_back(f);
}

void Screen::deleteForce(Force * f)
{
    for (unsigned int i = 0; i<_forces.size(); i++)
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
        for (unsigned int i = 0; i<colliders->size(); i++)
        {
            if (c==colliders->at(i))
            {
                colliders->erase(colliders->begin()+i);
                return;
            }
        }
    }
}

void Screen::setCamera(Camera *cam)
{
    _camera = cam;
}

Camera *Screen::getCamera()
{
    return _camera;
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
















