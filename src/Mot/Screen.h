#ifndef SCREEN_H
#define SCREEN_H

#include "WorldElement.h"
#include "Force.h"
#include "Collider.h"

#include <vector>
#include <map>


#ifdef IN_QT
#include <QGraphicsScene>
#include <QGraphicsView>

#else

#endif

class Screen : public WorldElement
{
private:

#ifdef IN_QT
    QGraphicsView * _view;
    QGraphicsScene * _scene;

#else

#endif
protected:

    std::vector<WorldElement*> _worldElements;
    std::vector<Force*> _forces;
    std::map<int, std::vector<Collider*>* > _collisionLayers;


public:
    Screen();
    virtual ~Screen();
    virtual int update(double seconds);
    virtual int draw(Vector2d pos = Vector2d());

    // Fonctions d'ajout/delete
    void addWorldElement(WorldElement* we);
    void deleteWorldElement(WorldElement* we);

    void addForce(Force* f);
    void deleteForce(Force* f);

    void addCollider(int layer, Collider* c);
    void deleteCollider(int layer, Collider* c);

#ifdef IN_QT
    void hide();
    void show();

#else

#endif

};

#endif // SCREEN_H
