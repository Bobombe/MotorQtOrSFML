
#include "ScreenManagerTest.h"

ScreenManagerTest::ScreenManagerTest():
    _stateMachine(0)
{
    _titleScreen = new tu::TitleScreen();
    addScreen(0, _titleScreen);
    setCurrentScreenId(0);
}

ScreenManagerTest::~ScreenManagerTest()
{
}

void ScreenManagerTest::update(double, int, int drawReturn)
{
    if (drawReturn && _stateMachine==0) {
        _stateMachine = 1;
        _level1 = new Level1();
        startScreen(_stateMachine, _level1);
    }
}

void ScreenManagerTest::startScreen(int screenId, Screen *screen)
{
    addScreen(screenId, screen);
    setCurrentScreenId(screenId);
    screen->initScreen();
}
