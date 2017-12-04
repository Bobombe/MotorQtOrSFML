#ifndef GAMEOVERBUTTON_H
#define GAMEOVERBUTTON_H

#include "Button.h"
#include "Mot/Text.h"

class GameOverButton : public Button
{

protected:
    Text * _gameOverText;

public:
    GameOverButton();
    virtual ~GameOverButton();

protected:

private:
};

#endif // GAMEOVERBUTTON_H
