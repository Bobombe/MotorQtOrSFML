
#ifndef SRC_SCREENLEVEL1_H_
#define SRC_SCREENLEVEL1_H_

#include "Mot/Screen.h"
#include "Mot/Text.h"
#include "Spaceship.h"
#include "Mot/Button.h"

class ScreenLevel1 : public Screen
{
protected:
    double _opponentCoolDown;
    int _state;
    Spaceship * _player;

    // Interface points
    Text* _creditsLabel;
    Text* _creditsValue;
    Text* _powerLabel;
    Text* _powerValue;
    Text* _happinessLabel;

    bool _gameOver;
    Button* _goButton;


public:
    static const int SIZEX;
    static const int SIZEY;
    ScreenLevel1();
    virtual ~ScreenLevel1();
protected:
    virtual int update(double seconds);
    virtual int draw();
    void randSpawn();
};

#endif
