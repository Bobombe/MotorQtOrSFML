
#include "EventsManager.h"
#include "KeyboardListener.h"
#include "MouseListener.h"
#include <iostream>
#include "moteur2d.h"
#include "Vector2d.h"

#ifdef IN_QT
#include <QKeyEvent>
#include <QObject>
#endif

EventsManager::EventsManager()
{
#ifdef IN_QT
    setMouseTracking(true);
    _layout.setParent(this);
    setLayout(&_layout);

#endif
}

EventsManager::~EventsManager()
{
}


#ifdef IN_QT
bool EventsManager::eventFilter(QObject *obj, QEvent *event)
{
    bool retValue = true;
    switch (event->type()) {
        case QEvent::KeyPress: {
            QKeyEvent * kevent = dynamic_cast<QKeyEvent *>(event);
            if (kevent) {
                keyPressEvent(kevent);
            }
        }
            break;
        case QEvent::KeyRelease: {
            QKeyEvent * kevent = dynamic_cast<QKeyEvent *>(event);
            if (kevent) {
                keyReleaseEvent(kevent);
            }
        }
            break;
        case QEvent::MouseMove: {
            QMouseEvent * mEvent = dynamic_cast<QMouseEvent *>(event);
            if (mEvent) {
                mouseMoveEvent(mEvent);
            }
        }
            break;
        case QEvent::MouseButtonPress: {
            QMouseEvent * mEvent = dynamic_cast<QMouseEvent *>(event);
            if (mEvent) {
                mousePressEvent(mEvent);
            }
        }
            break;
        case QEvent::MouseButtonRelease: {
            QMouseEvent * mEvent = dynamic_cast<QMouseEvent *>(event);
            if (mEvent) {
                mouseReleaseEvent(mEvent);
            }
        }
            break;
        case QEvent::Wheel: {
            QWheelEvent * mEvent = dynamic_cast<QWheelEvent *>(event);
            if (mEvent) {
                wheelEvent(mEvent);
            }
        }
            break;
        default:
            retValue = QObject::eventFilter(obj, event);
            break;
    }
    return retValue;
}
void EventsManager::keyPressEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat()) {
		std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
		for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
		{
		    if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdKeyboard()) {
		        it->second->keyPressed(KeyboardListener::retrieveKeyFromQt(event->key()));
		    }
		}
	}
}
void EventsManager::keyReleaseEvent(QKeyEvent * event)
{
	if (!event->isAutoRepeat()) {
		std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
		for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
		{
            if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdKeyboard()) {
                it->second->keyReleased(KeyboardListener::retrieveKeyFromQt(event->key()));
            }
		}
	}
}

void EventsManager::mouseMoveEvent(QMouseEvent * event)
{
	Vector2d mousePos;
	mousePos.x = event->x()-12;
	mousePos.y = event->y()-12;

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
            it->second->mouseMoved(mousePos);
        }
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
	mousePos.x = event->x()-12;
	mousePos.y = event->y()-12;

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
            it->second->buttonPressed(mb, mousePos);
        }
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
	mousePos.x = event->x()-12;
	mousePos.y = event->y()-12;

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
            it->second->buttonReleased(mb, mousePos);
        }
    }
}
void EventsManager::wheelEvent(QWheelEvent * event)
{
	float degreeMove = event->angleDelta().y()/8.;

    std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
    for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
    {
        if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
            it->second->mouseWheelMoved(degreeMove);
        }
    }
}

#else

void EventsManager::eventLoop(sf::RenderWindow &window)
{

    while (window.pollEvent(_sfEvent))
    {
        // Click sur la croix -> Fermeture
        if(_sfEvent.type == sf::Event::Closed)
            window.close();

        // Appuis sur touche -> Appel des listener de clavier
        else if (_sfEvent.type == sf::Event::KeyPressed)
        {
            std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
            for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
            {
                if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdKeyboard()) {
                    it->second->keyPressed((Key::Key)_sfEvent.key.code);
                }
            }
        }
        // Relachement d'une touche -> Appel des listener de clavier
        else if (_sfEvent.type == sf::Event::KeyReleased)
        {
            std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
            for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
            {
                if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdKeyboard()) {
                    it->second->keyReleased((Key::Key)_sfEvent.key.code);
                }
            }
        }

        // Appuis sur un bouton de la souris -> Appel des listener de souris
        else if (_sfEvent.type == sf::Event::MouseButtonPressed)
        {
        	MouseButton::MouseButton mb = MouseButton::left;
        	if (_sfEvent.mouseButton.button == sf::Mouse::Left) {
        		mb = MouseButton::left;
        	} else if (_sfEvent.mouseButton.button == sf::Mouse::Right) {
        		mb = MouseButton::right;
        	} else if (_sfEvent.mouseButton.button == sf::Mouse::Middle) {
				mb = MouseButton::middle;
			} else {
				mb = MouseButton::Unknown;
			}

        	Vector2d mousePos;
        	mousePos.x = _sfEvent.mouseButton.x;
        	mousePos.y = _sfEvent.mouseButton.y;

            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
                    it->second->buttonPressed(mb, mousePos);
                }
            }
        }
        // Relachement d'un bouton de la souris -> Appel des listener de souris
        else if (_sfEvent.type == sf::Event::MouseButtonReleased)
        {
        	MouseButton::MouseButton mb = MouseButton::left;
        	if (_sfEvent.mouseButton.button == sf::Mouse::Left) {
        		mb = MouseButton::left;
        	} else if (_sfEvent.mouseButton.button == sf::Mouse::Right) {
        		mb = MouseButton::right;
        	} else if (_sfEvent.mouseButton.button == sf::Mouse::Middle) {
				mb = MouseButton::middle;
			} else {
				mb = MouseButton::Unknown;
			}

        	Vector2d mousePos;
        	mousePos.x = _sfEvent.mouseButton.x;
        	mousePos.y = _sfEvent.mouseButton.y;

            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {

                if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
                    it->second->buttonReleased(mb, mousePos);
                }
            }
        }
        // Mouvement de la souris -> Appel des listener de souris
        else if (_sfEvent.type == sf::Event::MouseMoved)
        {
        	Vector2d mousePos;
        	mousePos.x = _sfEvent.mouseMove.x;
        	mousePos.y = _sfEvent.mouseMove.y;

            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
                    it->second->mouseMoved(mousePos);
                }
            }
        }
        // Mouvement molette de la souris -> Appel des listener de souris
        else if (_sfEvent.type == sf::Event::MouseWheelMoved)
        {
            std::map<int,MouseListener*> mls = Moteur2D::getInstance()->getMouseListeners();
            for (std::map<int,MouseListener*>::iterator it=mls.begin(); it!=mls.end(); ++it)
            {
                if (Moteur2D::getInstance()->getCurrentScreenId() == it->second->getScreenIdMouse()) {
                    it->second->mouseWheelMoved(_sfEvent.mouseWheel.delta*15); // In most case, a "tick" is 15 degree
                }
            }
        }
    }
}
#endif
