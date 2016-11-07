
#include "EventsManager.h"
#include "KeyboardListener.h"
#include "MouseListener.h"
#include <iostream>
#include "moteur2d.h"
#include "Vector2d.h"

#ifdef IN_QT
#include <QKeyEvent>
#endif

EventsManager::EventsManager()
{
#ifdef IN_QT
    setMouseTracking(true);

#endif
}

EventsManager::~EventsManager()
{
}


#ifdef IN_QT
void EventsManager::keyPressEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat()) {
		std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
		for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
		{
			it->second->keyPressed(KeyboardListener::retrieveKeyFromQt(event->key()));
		}
	}
}
void EventsManager::keyReleaseEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat()) {
		std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
		for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
		{
			it->second->keyReleased(KeyboardListener::retrieveKeyFromQt(event->key()));
		}
	}
}

void EventsManager::mouseMoveEvent(QMouseEvent * event)
{
	Vector2d mousePos;
	mousePos.x = event->x();
	mousePos.y = event->y();

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        it->second->mouseMoved(mousePos);
    }
}
void EventsManager::mousePressEvent(QMouseEvent * event)
{
	MouseButton::MouseButton mb = MouseButton::left;

	switch (event->button())
	{
	case Qt::LeftButton:
		mb = MouseButton::left;
		break;
	case Qt::RightButton:
		mb = MouseButton::right;
		break;
	case Qt::MiddleButton:
		mb = MouseButton::middle;
		break;
	default:
		mb = MouseButton::Unknown;
	}

	Vector2d mousePos;
	mousePos.x = event->x();
	mousePos.y = event->y();

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        it->second->buttonPressed(mb, mousePos);
    }
}
void EventsManager::mouseReleaseEvent(QMouseEvent * event)
{
	MouseButton::MouseButton mb = MouseButton::left;

	switch (event->button())
	{
	case Qt::LeftButton:
		mb = MouseButton::left;
		break;
	case Qt::RightButton:
		mb = MouseButton::right;
		break;
	case Qt::MiddleButton:
		mb = MouseButton::middle;
		break;
	default:
		mb = MouseButton::Unknown;
	}

	Vector2d mousePos;
	mousePos.x = event->x();
	mousePos.y = event->y();

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        it->second->buttonReleased(mb, mousePos);
    }
}
void EventsManager::wheelEvent(QWheelEvent * event)
{
	float degreeMove = event->angleDelta().y()/8.;

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        it->second->mouseWheelMoved(degreeMove);
    }
}

#else

void EventsManager::eventLoop(sf::RenderWindow &window)
{
    std::cout << "EventsManager::eventLoop " << std::endl;
}
#endif
