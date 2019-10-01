#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "../Mot/Button.h"
#include "../Mot/Screen.h"
#include "../Mot/Sound.h"

class TitleScreen: public Screen
{
protected:
    Button _bt;
    Sound _sound;

public:
    TitleScreen();
    virtual ~TitleScreen();

protected:
    virtual int draw();
};

#endif // TITLESCREEN_H
