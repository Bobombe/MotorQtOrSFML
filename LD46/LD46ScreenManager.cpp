
#include "LD46ScreenManager.h"

LD46ScreenManager::LD46ScreenManager():
    _stateMachine(0)
{
    _titleScreen = new LD46TitleScreen();
    addScreen(0, _titleScreen);
    setCurrentScreenId(0);
}

LD46ScreenManager::~LD46ScreenManager()
{
}

void LD46ScreenManager::update(double, int, int drawReturn)
{
    if (drawReturn && _stateMachine==0) {
        _stateMachine = 1;
        _level1 = new Level1();
        startScreen(_stateMachine, _level1);
    }
}

void LD46ScreenManager::startScreen(int screenId, Screen *screen)
{
    addScreen(screenId, screen);
    setCurrentScreenId(screenId);
    screen->initScreen();
}
