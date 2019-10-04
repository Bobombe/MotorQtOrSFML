#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"

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
