#ifndef TU_LD46TITLESCREEN_H
#define TU_LD46TITLESCREEN_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"

class LD46TitleScreen: public Screen
{
protected:
    Button _bt;
    Sound _sound;

public:
    LD46TitleScreen();
    virtual ~LD46TitleScreen();

protected:
    virtual int draw();
};

#endif // TU_LD46TITLESCREEN_H
