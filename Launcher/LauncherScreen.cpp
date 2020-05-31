#include "LauncherScreen.h"
#include "moteur2d.h"
#include "Sound.h"

#include "LD45/ScreenManagerLD45.h"
#include "LD46/LD46ScreenManager.h"
#include "TU/ScreenManagerTest.h"

LauncherScreen::LauncherScreen():
    Screen(),
    _btLD45(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 120),"LD45", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 120),"LD45", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 120),"LD45", Color::Green)),
    _btLD46(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 120),"LD46", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 120),"LD46", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 120),"LD46", Color::Green)),
    _btTU(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 120),"TU", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 120),"TU", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 120),"TU", Color::Green)),
    /*_bt(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 120),"Ready?", Text::Color::Black),
        Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 120),"START!", Text::Color::Red),
        Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 120),"SET...", Text::Color::Green)),*/
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

    Vector2d basePosition(Moteur2D::getInstance()->getScreenSize().x / 2 - 200, Moteur2D::getInstance()->getScreenSize().y / 2 - 60);
    Vector2d offset(0, 130);

    _btLD45.setPosition(basePosition-offset); _btLD45.setScreenId(0); _btLD45.setParent(this); _btLD45.setVisible(false);
    _btLD46.setPosition(basePosition); _btLD46.setScreenId(0); _btLD46.setParent(this); _btLD46.setVisible(false);
    _btTU.setPosition(basePosition+offset); _btTU.setScreenId(0); _btTU.setParent(this); _btTU.setVisible(false);

    setPosition(Vector2d(0, -Moteur2D::getInstance()->getScreenSize().y));
    setSpeed(Vector2d(0, 300));
}

LauncherScreen::~LauncherScreen()
{
    std::cout << "Youpi : del LauncherScreen" << std::endl;
}

int LauncherScreen::draw()
{
    int retValue = 0;
    if (getPosition().y >= 0) {
        setSpeed(Vector2d(0, 0));
        setPosition(Vector2d(0, 0));
        _btLD45.setVisible();
        _btLD46.setVisible();
        _btTU.setVisible();
    }
    if (_btLD45.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new ScreenManagerLD45());
    }
    if (_btLD46.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new LD46ScreenManager());
    }
    if (_btTU.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new ScreenManagerTest());
    }
    Screen::draw();
    return retValue;
}
