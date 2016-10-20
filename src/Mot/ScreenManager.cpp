
#include "ScreenManager.h"
#include <iostream>
#include <stdexcept>

ScreenManager::ScreenManager() {

}

ScreenManager::~ScreenManager() {
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
