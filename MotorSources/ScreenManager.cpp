
#include "ScreenManager.h"
#include <iostream>
#include <stdexcept>

ScreenManager::ScreenManager() : _currentScreen(-1)
{

}

ScreenManager::~ScreenManager()
{
    for (auto screen : _screens) {
        if (screen.second) {
            delete screen.second;
        }
    }
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


void ScreenManager::addScreen(int screenId,Screen*s)
{
    if (_screens.find(screenId) != _screens.end()) {
        std::cerr << "Trying to add a screen at the id("<< screenId <<") already taken" << std::endl;
        if (_screens[screenId]) {
            delete _screens[screenId];
        }
    }
    _screens[screenId] = s;
    s->setScreenId(screenId);
}

Screen *ScreenManager::removeScreen(int screenId)
{
    Screen * retScreen{nullptr};
    if (_screens[screenId]) {
        retScreen = _screens[screenId];
        _screens[screenId] = nullptr;
    }
    return retScreen;
}

void ScreenManager::deleteScreen(int screenId)
{
    if (_screens[screenId]) {
        delete _screens[screenId];
        _screens[screenId] = nullptr;
    }
}

Screen* ScreenManager::screenAt(int indexOfScreen)
{
    Screen * scr = nullptr;
    try
    {
        scr = _screens.at(indexOfScreen);
    }
    catch (const std::out_of_range&)
    {
        std::cout << "ERROR : no Screen at index " << indexOfScreen << std::endl;
        scr = nullptr;
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








