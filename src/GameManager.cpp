
#include "GameManager.h"
#include "StartScreen.h"

GameManager::GameManager() : _stateMachine(0)
{
    addScreen(0, new StartScreen());
    _currentScreen = 0;
}

GameManager::~GameManager()
{
}



void GameManager::update(double seconds)
{
}
