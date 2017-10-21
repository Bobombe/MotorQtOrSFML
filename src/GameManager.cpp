
#include "GameManager.h"
#include "StartScreen.h"
#include "ScreenLevel1.h"

GameManager::GameManager() : _stateMachine(0)
{
    addScreen(0, new StartScreen());
    addScreen(1, new ScreenLevel1());
    _currentScreen = 0;
}

GameManager::~GameManager()
{
}



void GameManager::update(double seconds, int updateReturn, int drawReturn)
{
    if (drawReturn == 1 && _currentScreen == 0) {
        delete getCurrentScreen();
        _currentScreen = 1;
    }
}
