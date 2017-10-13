
#include "ScreenManager.h"
#include <iostream>
#include <stdexcept>

ScreenManager::ScreenManager() : _currentScreen(0)
{

}

ScreenManager::~ScreenManager() {
}

void ScreenManager::baseUpdate(double seconds)
{
    update(seconds);

    Screen * scr = screen(_currentScreen);
    if (scr) {
        scr->baseUpdate(seconds);
        scr->baseDraw();
    } else {
        std::cout << "[ERROR] : No current screen set" << std::endl;
    }
}


void ScreenManager::addScreen(int k,Screen*s)
{
    _screens[k] = s;
}


Screen* ScreenManager::screen(int indexOfScreen)
{
    Screen * scr = 0;
    try
    {
        scr = _screens.at(indexOfScreen);
    }
    catch (const std::out_of_range& oor)
    {
        std::cout << "ERROR : no Screen at index " << indexOfScreen << std::endl;
        scr = 0;
    }
    return scr;
}

Screen* ScreenManager::getCurrentScreen()
{
    return screen(_currentScreen);
}

int ScreenManager::getCurrentScreenId()
{
    return _currentScreen;
}
