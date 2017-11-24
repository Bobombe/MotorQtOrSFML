
#include "GameManager.h"
#include "StartScreen.h"
#include "ScreenLevel1.h"

GameManager::GameManager() : _stateMachine(0)
{
    addScreen(0, new StartScreen());
    addScreen(1, new ScreenLevel1());
    setCurrentScreenId(0);
}

GameManager::~GameManager()
{
}



void GameManager::update(double seconds, int updateReturn, int drawReturn)
{
    if (drawReturn == 1 && getCurrentScreenId() == 0) {
        // delete getCurrentScreen();
        setCurrentScreenId(1);
    }
}
