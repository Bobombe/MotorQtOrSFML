#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../Mot/Button.h"
#include "../Mot/Screen.h"

class TitleScreen: public Screen
{
protected:
    Button _bt;

public:
    TitleScreen();
    virtual ~TitleScreen();

protected:
    virtual int draw();
};

#endif // TITLESCREEN_H
