
#include "ScreenManagerTest.h"
#include "TitleScreen.h"

ScreenManagerTest::ScreenManagerTest():
    _stateMachine(0)
{
    addScreen(0, new TitleScreen());
    setCurrentScreenId(0);
}

ScreenManagerTest::~ScreenManagerTest()
{
}

void ScreenManagerTest::update(double seconds, int updateReturn, int drawReturn)
{
}
