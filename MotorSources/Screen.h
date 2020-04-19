#ifndef SCREEN_H
#define SCREEN_H

#include "WorldElement.h"
#include "Force.h"
#include "Collider.h"
#include "Camera.h"

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

#else

#endif
protected:

    std::vector<Force*> _forces;
    std::map<int, std::vector<Collider*>* > _collisionLayers;
    Camera * _camera;

    bool _screenInitialized;


public:
    Screen(Camera * camera = nullptr);
    virtual ~Screen();

    // Fonctions d'ajout/delete
    void addForce(Force* f);
    void deleteForce(Force* f);

    void addCollider(int layer, Collider* c);
    void deleteCollider(int layer, Collider* c);

    void setScreenId(int screenId){_screenId = screenId;}
    int getScreenId(){return _screenId;}

    void setCamera(Camera * cam);
    Camera* getCamera();

    virtual void initScreen(){}

#ifdef IN_QT
    void hide();
    void show();

#else

#endif

protected:
    virtual int update(double seconds);

private:
    int _screenId{-1};

};

#endif // SCREEN_H
