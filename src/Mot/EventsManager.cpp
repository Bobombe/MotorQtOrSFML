
#include "EventsManager.h"
#include "KeyboardListener.h"
#include <iostream>

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
    std::cout << "EventsManager::keyPressEvent " << event->key() << " ; converted = " << KeyboardListener::retrieveKeyFromQt(event->key()) << std::endl;
//    std::map<int,KeyboardListener*> kls = Moteur2D::getInstance()->getKeyboardListeners();
//    for (std::map<int,KeyboardListener*>::iterator it=kls.begin(); it!=kls.end(); ++it)
//    {
//        it->second->keyPressed(m_e.key.code);
//    }
}
void EventsManager::keyReleaseEvent(QKeyEvent * event)
{
    std::cout << "EventsManager::keyReleaseEvent " << std::endl;
}

void EventsManager::mouseMoveEvent(QMouseEvent * event)
{
    std::cout << "EventsManager::mouseMoveEvent " << std::endl;
}
void EventsManager::mousePressEvent(QMouseEvent * event)
{
    std::cout << "EventsManager::mousePressEvent " << std::endl;
}
void EventsManager::mouseReleaseEvent(QMouseEvent * event)
{
    std::cout << "EventsManager::mouseReleaseEvent " << std::endl;
}
void EventsManager::wheelEvent(QWheelEvent * event)
{
    std::cout << "EventsManager::wheelEvent " << std::endl;
}

#else

void EventsManager::eventLoop(sf::RenderWindow &window)
{
    std::cout << "EventsManager::eventLoop " << std::endl;
}
#endif
