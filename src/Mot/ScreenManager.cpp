
#include "ScreenManager.h"
#include <iostream>
#include <stdexcept>

ScreenManager::ScreenManager() : _currentScreen(-1)
{

}

ScreenManager::~ScreenManager() {
}

void ScreenManager::baseUpdate(double seconds)
{
    Screen * scr = screenAt(_currentScreen);
    int updateReturn = -1;
    int drawReturn = -1;
    if (scr) {
        updateReturn = scr->baseUpdate(seconds);
        drawReturn = scr->baseDraw();
    } else {
        std::cout << "[ERROR] : No current screen set" << std::endl;
    }
    update(seconds, updateReturn, drawReturn);
}


void ScreenManager::addScreen(int k,Screen*s)
{
    _screens[k] = s;
}


Screen* ScreenManager::screenAt(int indexOfScreen)
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
    return screenAt(_currentScreen);
}

int ScreenManager::getCurrentScreenId()
{
    return _currentScreen;
}
void ScreenManager::setCurrentScreenId(int screenId)
{
#ifdef IN_QT
    if (_currentScreen >=0) {
        Screen* screen = screenAt(_currentScreen);
        if (screen) {
            screen->hide();
        }
    }
    if (screenId >=0) {
        Screen* screen = screenAt(screenId);
        if (screen) {
            screen->show();
        }
    }

#else

#endif
    _currentScreen = screenId;
}
