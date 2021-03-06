#include "TitleScreen.h"
#include "moteur2d.h"
#include "Sound.h"

namespace tu {
TitleScreen::TitleScreen():
    Screen(),
    _bt(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 120),"Ready?", Color::Black),
        Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 120),"START!", Color::Red),
        Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 120),"SET...", Color::Green)),
    _sound("./Ressources/FirstTryAtCoolSong.ogg")
{
    Sprite *s = new Sprite("./Ressources/Fond3.png");
    s->setParent(this);
    Sprite *sgn = new Sprite("./Ressources/sgn.png");
    sgn->setParent(s);
    sgn->setPosition(Vector2d(s->getSize().x-sgn->getSize().x-10, s->getSize().y-sgn->getSize().y));

    Button *b = new Button(Button::StateConfiguration("", Vector2d(0, 0), Vector2d(0, 0),"Ready?", Color::Black),
             Button::StateConfiguration("", Vector2d(0, 0), Vector2d(0, 0),"START!", Color::Red),
             Button::StateConfiguration("", Vector2d(0, 0), Vector2d(0, 0),"SET...", Color::Green));
    b->setParent(s);
    b->setPosition(Vector2d(100, 10));
    b->setScreenId(0);

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
        if (_sound.isPlaying()) {
            _sound.pause();
        } else {
            _sound.play();
        }

    }
    Screen::draw();
    return retValue;
}
}
