
#include "LauncherScreenManager.h"
#include "LauncherScreen.h"

LauncherScreenManager::LauncherScreenManager():
    _stateMachine(0)
{
    addScreen(0, new LauncherScreen());
    setCurrentScreenId(0);
}

LauncherScreenManager::~LauncherScreenManager()
{
}

void LauncherScreenManager::update(double, int, int)
{
}
