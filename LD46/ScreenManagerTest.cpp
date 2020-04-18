
#include "ScreenManagerTest.h"
#include "TU/TitleScreen.h"

ScreenManagerTest::ScreenManagerTest():
    _stateMachine(0)
{
    addScreen(0, new tu::TitleScreen());
    setCurrentScreenId(0);
}

ScreenManagerTest::~ScreenManagerTest()
{
}

void ScreenManagerTest::update(double, int, int)
{
}
