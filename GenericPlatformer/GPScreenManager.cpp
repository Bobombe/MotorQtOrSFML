
#include "GPScreenManager.h"
#include "GPScreen.h"

GPScreenManager::GPScreenManager():
    _stateMachine(0)
{
    addScreen(0, new GPScreen());
    setCurrentScreenId(0);
}

GPScreenManager::~GPScreenManager()
{
}

void GPScreenManager::update(double, int, int)
{
}
