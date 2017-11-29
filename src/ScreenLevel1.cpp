
#include "ScreenLevel1.h"
#include "Mot/moteur2d.h"
#include "PersoTest.h"
#include "TestGravity.h"
#include "Mot/Collider.h"

ScreenLevel1::ScreenLevel1() : _zoomin(true)
{
    Sprite * s = new Sprite("./Ressources/Fond3.png");
    s->setParent(this);

    PersoTest* p = new PersoTest();
    p->setPosition(Vector2d(200, 0));
    p->setParent(this);
    addCollider(0, p->getCollider());
    p->setScreenId(1);

    TestGravity* tg = new TestGravity();
    tg->addWorldElement(p);
    addForce(tg);

    Sprite *block4 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(2000, 100));
    block4->setPosition(Vector2d(0, 600));
    block4->setParent(this);
    Collider *colBlock4 =  new Collider(block4);
    colBlock4->initRectangular(0, 0, block4->getSize().x, block4->getSize().y);
    addCollider(0, colBlock4);

    block4 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(2000, 1000));
    block4->setPosition(Vector2d(0, 6000));
    block4->setParent(this);
    colBlock4 =  new Collider(block4);
    colBlock4->initRectangular(0, 0, block4->getSize().x, block4->getSize().y);
    addCollider(0, colBlock4);

    _camera = new Camera();
    p->setCamera(_camera);
    block4 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40));
    block4->setPosition(Vector2d(-40, -40));
    block4->setParent(p);

}

ScreenLevel1::~ScreenLevel1()
{
    if (_camera) {
        delete _camera;
    }
}



int ScreenLevel1::update(double seconds)
{
//    if (_zoomin) {
//        _scale+=(seconds/5.);
//    } else {
//        _scale-=(seconds/5.);
//    }
//    if (_scale <= 0.6) {
//        _zoomin = true;
//    } else if (_scale >= 1.5) {
//        _zoomin = false;
//    }
    int ret = Screen::update(seconds);
    return ret;
}
