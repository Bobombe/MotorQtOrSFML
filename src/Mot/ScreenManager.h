
#ifndef SRC_MOT_SCREENMANAGER_H_
#define SRC_MOT_SCREENMANAGER_H_

#include "Screen.h"
#include <map>

class ScreenManager
{

protected:
    std::map<int,Screen *> _screens;
    int _currentScreen;

public:
    ScreenManager();
    virtual ~ScreenManager();

    void baseUpdate(double seconds);
    virtual void update(double seconds)=0;

    void addScreen(int,Screen*);

    Screen* screen(int indexOfScreen);
    Screen* getCurrentScreen();
    int getCurrentScreenId();

};

#endif /* SRC_MOT_SCREENMANAGER_H_ */
