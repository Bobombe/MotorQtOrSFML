
#include "ScreenLevel1.h"
#include "Mot/moteur2d.h"
#include "Spaceship.h"
#include "Opponent.h"
#include "Pod.h"
#include "Planet.h"
#include "Mot/Collider.h"
#include <string>
#include <stdlib.h>     /* srand, rand */

    const int ScreenLevel1::SIZEX(800);
    const int ScreenLevel1::SIZEY(1000);

ScreenLevel1::ScreenLevel1() : _opponentCoolDown(1), _state(5), _gameOver(false), _goButton(0)
{
    _weName = "ScreenLevel1";

    // Décord gauche
    Sprite * deco = 0;
//    deco = new Sprite("./resLD40/palette.png", Vector2d(30, 40), Vector2d(10, 10), Vector2d(SIZEX, SIZEY));
//    deco->setPosition(Vector2d(0,0));
//    deco->setParent(this);

    deco = new Sprite("./resLD40/palette.png", Vector2d(30, 30), Vector2d(10, 10), Vector2d(SIZEX, 5));
    deco->setPosition(Vector2d(0, 0));
    deco->setParent(this);
    Collider *colBord =  new Collider(deco);
    colBord->initRectangular(0, 0, deco->getSize().x, deco->getSize().y);
    addCollider(0, colBord);

    deco = new Sprite("./resLD40/palette.png", Vector2d(30, 30), Vector2d(10, 10), Vector2d(SIZEX, 5));
    deco->setPosition(Vector2d(0, SIZEY-5));
    deco->setParent(this);
    colBord =  new Collider(deco);
    colBord->initRectangular(0, 0, deco->getSize().x, deco->getSize().y);
    addCollider(0, colBord);

    deco = new Sprite("./resLD40/palette.png", Vector2d(30, 30), Vector2d(10, 10), Vector2d(5, SIZEY));
    deco->setPosition(Vector2d(0, 0));
    deco->setParent(this);
    colBord =  new Collider(deco);
    colBord->initRectangular(0, 0, deco->getSize().x, deco->getSize().y);
    addCollider(0, colBord);

    deco = new Sprite("./resLD40/palette.png", Vector2d(30, 30), Vector2d(10, 10), Vector2d(5, SIZEY));
    deco->setPosition(Vector2d(SIZEX-5, 0));
    deco->setParent(this);
    colBord =  new Collider(deco);
    colBord->initRectangular(0, 0, deco->getSize().x, deco->getSize().y);
    addCollider(0, colBord);

    // D�cord Droite
    deco = new Sprite("./resLD40/palette.png", Vector2d(20, 40), Vector2d(10, 10), Vector2d(1200-SIZEX, SIZEY));
    deco->setPosition(Vector2d(SIZEX,0));
    deco->setParent(this, 42);
    deco = new Sprite("./resLD40/palette.png", Vector2d(20, 20), Vector2d(10, 10), Vector2d(1200-SIZEX, 5));
    deco->setPosition(Vector2d(SIZEX, 0));
    deco->setParent(this, 42);
    deco = new Sprite("./resLD40/palette.png", Vector2d(20, 20), Vector2d(10, 10), Vector2d(1200-SIZEX, 5));
    deco->setPosition(Vector2d(SIZEX, SIZEY-5));
    deco->setParent(this, 42);
    deco = new Sprite("./resLD40/palette.png", Vector2d(20, 20), Vector2d(10, 10), Vector2d(5, SIZEY));
    deco->setPosition(Vector2d(SIZEX, 0));
    deco->setParent(this, 42);
    deco = new Sprite("./resLD40/palette.png", Vector2d(20, 20), Vector2d(10, 10), Vector2d(5, SIZEY));
    deco->setPosition(Vector2d(1195, 0));
    deco->setParent(this, 42);

    _player = new Spaceship();
    _player->setParent(this, 41);
    addCollider(0, _player->getCollider());
    _player->setScreenId(1);

    // Set Interface,
    _creditsLabel = new Text("Credits", this, 43);
    _creditsValue = new Text(this, 43);
    _powerLabel = new Text("Power", this, 43);
    _powerValue = new Text(this, 43);
    _happinessLabel = new Text("Passengers Happiness", this);
    _creditsLabel->setPosition(Vector2d(SIZEX + 10, 10));
    _creditsValue->setPosition(Vector2d(SIZEX + 200, 10));
    _powerLabel->setPosition(Vector2d(SIZEX + 10, 60));
    _powerValue->setPosition(Vector2d(SIZEX + 200, 60));
    _happinessLabel->setPosition(Vector2d(SIZEX + 40, 110));
}

ScreenLevel1::~ScreenLevel1()
{
}



int ScreenLevel1::update(double seconds)
{
    _opponentCoolDown-=seconds;
    if (_opponentCoolDown<0) {
        _opponentCoolDown = 0.5;
        randSpawn();
//        switch (_state) {
//        case 0:
//            new Opponent(_player, Opponent::OPP_BLACK, this);
//            break;
//        case 1:
//            new Opponent(_player, Opponent::OPP_WHITE, this);
//            break;
//        case 2:
//            new Opponent(_player, Opponent::OPP_YELLOW, this);
//            break;
//        case 3:
//            new Opponent(_player, Opponent::OPP_ORANGE, this);
//            break;
//        case 4:
//            new Opponent(_player, Opponent::OPP_PURPLE, this);
//            break;
//        case 5:
//            new Opponent(_player, Opponent::OPP_GREEN, this);
//            break;
//        case 6:
//            new Pod(_player, Planet::PLANET_GREEN, true, this);
//            break;
//        case 7:
//            new Pod(_player, Planet::PLANET_BLACK, false, this);
//            break;
//        case 8:
//            new Pod(_player, Planet::PLANET_ORANGE, false, this);
//            break;
//        case 9:
//            new Planet(Planet::PLANET_GREEN, true, this);
//            break;
//        case 10:
//            new Pod(_player, Planet::PLANET_GREEN, false, this);
//            break;
//        case 11:
//            new Pod(_player, Planet::PLANET_BLACK, true, this);
//            break;
//        case 12:
//            new Pod(_player, Planet::PLANET_ORANGE, false, this);
//            break;
//        case 13:
//            new Planet(Planet::PLANET_ORANGE, false, this);
//            break;
//        }
        _state++;
        if (_state >13) {
            _state = 5;
        }

    }
    int ret = 0;
    int credits, power;
    std::vector<Spaceship::PassengerStats> passengersHappiness;
    _player->getStats(credits, power, passengersHappiness);
    _creditsValue->setText(STOI(credits)+ " cr");
    _powerValue->setText(STOI(power)+ " %");

    if (power>0) {
        ret = Screen::update(seconds);
    } else {
        if (!_gameOver) {
            //ret = 42;
            _gameOver = true;
            _goButton = new Button("./resLD40/buttonGameOver.png", Vector2d(0, 0), Vector2d(200,100), "         Game Over\nClick here to play again");
            _goButton->setParent(this);
            _goButton->setScreenId(1);
            _goButton->setPosition(Vector2d(300, 400));
        } else if (_goButton->isActivated()) {
            ret = 42;
        }
        _goButton->baseUpdate(seconds);
    }
    return ret;
}
int ScreenLevel1::draw()
{
    return Screen::draw();

}
void ScreenLevel1::randSpawn()
{
    int choix = rand() % 42+0;
    int pos = rand() % 750 +10;
    bool left = pos < 380;
    Opponent * op = 0;
    switch (choix) {
    case 1:
        new Planet(Planet::PLANET_PURPLE, left, this);
        _opponentCoolDown = 2;
        break;
    case 2:
        new Planet(Planet::PLANET_ORANGE, left, this);
        _opponentCoolDown = 2;
        break;
    case 3:
        new Planet(Planet::PLANET_GREEN, left, this);
        _opponentCoolDown = 2;
        break;
    case 4:
        new Planet(Planet::PLANET_YELLOW, left, this);
        _opponentCoolDown = 2;
        break;
    case 5:
        new Planet(Planet::PLANET_WHITE, left, this);
        _opponentCoolDown = 2;
        break;
    case 6:
        new Planet(Planet::PLANET_BLACK, left, this);
        _opponentCoolDown = 2;
        break;
    case 7:
    case 8:
        new Pod(_player, Planet::PLANET_PURPLE, left, this);
        _opponentCoolDown = 1;
        break;
    case 9:
    case 10:
        new Pod(_player, Planet::PLANET_ORANGE, left, this);
        _opponentCoolDown = 1;
        break;
    case 11:
    case 12:
        new Pod(_player, Planet::PLANET_GREEN, left, this);
        _opponentCoolDown = 1;
        break;
    case 13:
    case 14:
        new Pod(_player, Planet::PLANET_YELLOW, left, this);
        _opponentCoolDown = 1;
        break;
    case 15:
    case 16:
        new Pod(_player, Planet::PLANET_WHITE, left, this);
        _opponentCoolDown = 1;
        break;
    case 17:
    case 18:
        new Pod(_player, Planet::PLANET_BLACK, left, this);
        _opponentCoolDown = 1;
        break;
    case 19:
    case 20:
    case 21:
    case 22:
        op = new Opponent(_player, Opponent::OPP_PURPLE, this);
        op->setPosition(Vector2d(pos, op->getPosition().y));
        break;
    case 23:
    case 24:
    case 25:
    case 26:
        op = new Opponent(_player, Opponent::OPP_ORANGE, this);
        op->setPosition(Vector2d(pos, op->getPosition().y));
        break;
    case 27:
    case 28:
    case 29:
    case 30:
        op = new Opponent(_player, Opponent::OPP_GREEN, this);
        op->setPosition(Vector2d(pos, op->getPosition().y));
        break;
    case 31:
    case 32:
    case 33:
    case 34:
        op = new Opponent(_player, Opponent::OPP_YELLOW, this);
        op->setPosition(Vector2d(pos, op->getPosition().y));
        break;
    case 35:
    case 36:
    case 37:
    case 38:
        op = new Opponent(_player, Opponent::OPP_WHITE, this);
        op->setPosition(Vector2d(pos, op->getPosition().y));
        break;
    case 39:
    case 40:
    case 41:
    case 42:
        op = new Opponent(_player, Opponent::OPP_BLACK, this);
        op->setPosition(Vector2d(pos, op->getPosition().y));
        break;
    }
}
