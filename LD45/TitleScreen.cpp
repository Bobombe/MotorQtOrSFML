#include "TitleScreen.h"
#include "moteur2d.h"
#include "Sound.h"

namespace ld45 {
TitleScreen::TitleScreen():
    Screen(),
    _bt("./Ressources/LD45Button.PNG", Vector2d(0, 240), Vector2d(305, 120),
        "./Ressources/LD45Button.PNG", Vector2d(0, 120), Vector2d(305, 120),
        "./Ressources/LD45Button.PNG", Vector2d(0, 0), Vector2d(305, 120))
{
    Sprite *s = new Sprite("./Ressources/Fond3.png");
    s->setParent(this);

    _bt.setScale(2);
    _bt.setPosition(Vector2d(Moteur2D::getInstance()->getScreenSize().x/2 - _bt.getSize().x*_bt.getScale()/2,
                             Moteur2D::getInstance()->getScreenSize().y/2 - _bt.getSize().y*_bt.getScale()/2));
    _bt.setScreenId(0);
    _bt.setParent(this);
    _bt.setVisible(false);

    setPosition(Vector2d(0, -Moteur2D::getInstance()->getScreenSize().y));
    setSpeed(Vector2d(0, 500));
}

TitleScreen::~TitleScreen()
{
}

int TitleScreen::draw()
{
    int retValue = 0;
    if (getPosition().y >= 0) {
        setSpeed(Vector2d(0, 0));
        setPosition(Vector2d(0, 0));
        _bt.setVisible();
    }
    if (_bt.isActivated()) {
        retValue = 1;
    }
    Screen::draw();
    return retValue;
}
}
