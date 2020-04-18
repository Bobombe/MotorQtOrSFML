#ifndef TU_TITLESCREEN_H
#define TU_TITLESCREEN_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"
namespace tu {
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
}
#endif // TU_TITLESCREEN_H
