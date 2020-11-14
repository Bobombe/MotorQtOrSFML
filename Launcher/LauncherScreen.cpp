#include "LauncherScreen.h"
#include "moteur2d.h"
#include "Sound.h"

#include "LD40/GameManager.h"
#include "LD45/ScreenManagerLD45.h"
#include "LD46/LD46ScreenManager.h"
#include "GenericPlatformer/GPScreenManager.h"
#include "TU/ScreenManagerTest.h"

LauncherScreen::LauncherScreen():
    Screen(),
    _btLD40(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(200, 50),"LD40", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(200, 50),"LD40", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(200, 50),"LD40", Color::Green)),
    _btLD45(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(200, 50),"LD45", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(200, 50),"LD45", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(200, 50),"LD45", Color::Green)),
    _btLD46(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(200, 50),"LD46", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(200, 50),"LD46", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(200, 50),"LD46", Color::Green)),
    _btGP(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(200, 50),"Platformer", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(200, 50),"Platformer", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(200, 50),"Platformer", Color::Green)),
    _btTU(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(200, 50),"TU", Color::Black),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(200, 50),"TU", Color::Red),
            Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(200, 50),"TU", Color::Green)),
    /*_bt(Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 0), Vector2d(400, 50),"Ready?", Text::Color::Black),
        Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 240), Vector2d(400, 50),"START!", Text::Color::Red),
        Button::StateConfiguration("./Ressources/Perso.PNG", Vector2d(0, 120), Vector2d(400, 50),"SET...", Text::Color::Green)),*/
    _sound("./Ressources/FirstTryAtCoolSong.ogg")
{
    Sprite *s = new Sprite("./Ressources/Fond3.png");
    s->setParent(this);
    Sprite *sgn = new Sprite("./Ressources/sgn.png");
    sgn->setParent(s);
    sgn->setPosition(Vector2d(s->getSize().x-sgn->getSize().x-10, s->getSize().y-sgn->getSize().y));

    _sound.setParent(s);
    _sound.play();

    Vector2d basePosition(Moteur2D::getInstance()->getScreenSize().x/2 - _btLD40.getSize().x/2, Moteur2D::getInstance()->getScreenSize().y/2 - _btLD40.getSize().y/2);
    int xOffset(250);
    int yOffset(80);

    _btLD40.setPosition(basePosition.x - xOffset/2, basePosition.y - yOffset); _btLD40.setScreenId(0); _btLD40.setParent(this); _btLD40.setVisible(false);
    _btLD45.setPosition(basePosition.x - xOffset/2, basePosition.y          ); _btLD45.setScreenId(0); _btLD45.setParent(this); _btLD45.setVisible(false);
    _btLD46.setPosition(basePosition.x - xOffset/2, basePosition.y + yOffset); _btLD46.setScreenId(0); _btLD46.setParent(this); _btLD46.setVisible(false);

    _btGP.setPosition  (basePosition.x + xOffset/2, basePosition.y - yOffset); _btGP.setScreenId(0); _btGP.setParent(this); _btGP.setVisible(false);
    _btTU.setPosition  (basePosition.x + xOffset/2, basePosition.y); _btTU.setScreenId(0); _btTU.setParent(this); _btTU.setVisible(false);

    // setPosition(Vector2d(0, -Moteur2D::getInstance()->getScreenSize().y));
    // setSpeed(Vector2d(0, 300));
}

LauncherScreen::~LauncherScreen()
{
}

int LauncherScreen::draw()
{
    int retValue = 0;
    if (!_btLD40.isVisible() && getPosition().y >= 0) {
        setSpeed(Vector2d(0, 0));
        setPosition(Vector2d(0, 0));
        _btLD40.setVisible();
        _btLD45.setVisible();
        _btLD46.setVisible();
        _btGP.setVisible();
        _btTU.setVisible();
    }
    if (_btLD40.isActivated()) {
        Moteur2D *moteur = Moteur2D::getInstance();

        moteur->changeResolution(1200, 1000, "LD40");
        Moteur2D::getInstance()->changeScreenManager(new GameManager());
    }
    if (_btLD45.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new ScreenManagerLD45());
    }
    if (_btLD46.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new LD46ScreenManager());
    }
    if (_btGP.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new GPScreenManager());
    }
    if (_btTU.isActivated()) {
        Moteur2D::getInstance()->changeScreenManager(new ScreenManagerTest());
    }
    Screen::draw();
    return retValue;
}
