#ifndef SCREEN_H
#define SCREEN_H

#include "WorldElement.h"

#include <vector>


#ifdef IN_QT
#include <QGraphicsScene>
#include <QGraphicsView>

#else

#endif

class Screen : public WorldElement
{
protected:

#ifdef IN_QT
    QGraphicsScene * _scene;

#else

#endif

    std::vector<WorldElement*> _worldElements;


public:
    Screen();
    virtual ~Screen();
    virtual int update(double seconds);
    virtual int draw(Vector2d pos = Vector2d());

    // Fonctions d'ajout
    void addWorldElement(WorldElement*);

    void deleteWorldElement(WorldElement*);

};

#endif // SCREEN_H
