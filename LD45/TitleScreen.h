#ifndef LD45_TITLESCREEN_H
#define LD45_TITLESCREEN_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"

namespace ld45 {
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
}
#endif // LD45_TITLESCREEN_H
