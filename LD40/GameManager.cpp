
#include "GameManager.h"
#include "StartScreenLD40.h"
#include "ScreenLevel1.h"

GameManager::GameManager() : _stateMachine(0)
{
    addScreen(0, new StartScreenLD40());
    addScreen(1, new ScreenLevel1());
    setCurrentScreenId(0);
}

GameManager::~GameManager()
{
}



void GameManager::update(double, int updateReturn, int drawReturn)
{
    if (drawReturn == 1 && getCurrentScreenId() == 0) {
        // delete getCurrentScreen();
        setCurrentScreenId(1);
    }
    if (updateReturn == 42 && getCurrentScreenId() == 1) {
        setCurrentScreenId(0);
        auto s = removeScreen(1);
        if (s) delete s;
        this->addScreen(1, new ScreenLevel1());
    }
}
