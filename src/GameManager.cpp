
#include "GameManager.h"
#include "StartScreen.h"

GameManager::GameManager() : _stateMachine(0)
{
    addScreen(0, new StartScreen());
}

GameManager::~GameManager()
{
}



void GameManager::update(double seconds)
{
    Screen * scr = screen(_stateMachine);
    scr->update(seconds);
    scr->draw();
}
