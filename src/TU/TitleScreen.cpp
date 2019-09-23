#include "TitleScreen.h"
#include "../Mot/moteur2d.h"
#include "../Mot/Sound.h"

TitleScreen::TitleScreen():
    Screen(),
    _bt("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 120),
        "./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 120),
        "./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 120),"GO!"),
    _sound("./Ressources/Footsteps_on_Cement.wav")
{
    Sprite *s = new Sprite("./Ressources/Fond3.png");
    s->setParent(this);

    _sound.setParent(s);
    _sound.play();

    _bt.setPosition(Vector2d(Moteur2D::getInstance()->getScreenSize().x / 2 - 200, Moteur2D::getInstance()->getScreenSize().y / 2 - 60));
    _bt.setScreenId(0);
    _bt.setParent(this);
    _bt.setVisible(false);

    setPosition(Vector2d(0, -Moteur2D::getInstance()->getScreenSize().y));
    setSpeed(Vector2d(0, 300));
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
        _sound.stop();
    }
    Screen::draw();
    return retValue;
}
