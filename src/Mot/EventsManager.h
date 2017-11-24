
#ifndef SRC_MOT_EVENTSMANAGER_H_
#define SRC_MOT_EVENTSMANAGER_H_


#ifdef IN_QT
#include <QWidget>
#include <QHBoxLayout>

#else

#include <SFML/Graphics.hpp>
#endif

class EventsManager
#ifdef IN_QT
: public QWidget

#else
#endif
{

#ifdef IN_QT
Q_OBJECT
#endif

protected:

#ifdef IN_QT
QHBoxLayout _layout;
#else

sf::Event _sfEvent;
#endif

public:
    EventsManager();
    virtual ~EventsManager();
#ifdef IN_QT
    bool eventFilter(QObject *obj, QEvent *event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);

    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void wheelEvent(QWheelEvent * event);

#else

    void eventLoop(sf::RenderWindow &window);
#endif
};

#endif /* SRC_MOT_EVENTSMANAGER_H_ */
