#ifndef Launcher_LauncherScreen_H
#define Launcher_LauncherScreen_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"
class LauncherScreen: public Screen
{
protected:
    Button _btLD40;
    Button _btLD45;
    Button _btLD46;
    Button _btGP;
    Button _btTU;
    Sound _sound;

public:
    LauncherScreen();
    virtual ~LauncherScreen();

protected:
    virtual int draw();
};
#endif // Launcher_LauncherScreen_H
