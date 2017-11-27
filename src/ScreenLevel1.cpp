
#include "ScreenLevel1.h"
#include "Mot/moteur2d.h"
#include "PersoTest.h"
#include "TestGravity.h"
#include "Mot/Collider.h"

ScreenLevel1::ScreenLevel1() : _zoomin(true)
{
    addWorldElement(new Sprite("./Ressources/Fond3.png"));

    PersoTest* p = new PersoTest();
    p->setPosition(Vector2d(200, 0));
    addWorldElement(p);
    addCollider(0, p->getCollider());
    p->setScreenId(1);

    TestGravity* tg = new TestGravity();
    tg->addWorldElement(p);
    addForce(tg);

    Sprite *block4 = new Sprite("./Ressources/sprite.png", Vector2d(20, 40), Vector2d(40, 40), Vector2d(1000, 100));
    block4->setPosition(Vector2d(0, 600));
    addWorldElement(block4);
    Collider *colBlock4 =  new Collider(block4);
    colBlock4->initRectangular(0, 0, block4->getSize().x, block4->getSize().y);
    addCollider(0, colBlock4);

}

ScreenLevel1::~ScreenLevel1()
{
}



int ScreenLevel1::update(double seconds)
{
    if (_zoomin) {
        _scale+=(seconds/5.);
    } else {
        _scale-=(seconds/5.);
    }
    if (_scale <= 0.6) {
        _zoomin = true;
    } else if (_scale >= 1.5) {
        _zoomin = false;
    }
    return Screen::update(seconds);
}
