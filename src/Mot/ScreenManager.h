
#ifndef SRC_MOT_SCREENMANAGER_H_
#define SRC_MOT_SCREENMANAGER_H_

#include "Screen.h"

class ScreenManager
{

protected:
    std::map<int,Screen *> _screens;

public:
    ScreenManager();
    virtual ~ScreenManager();

    virtual void update(double seconds)=0;

    void addScreen(int,Screen*);

    Screen* screen(int indexOfScreen);

};

#endif /* SRC_MOT_SCREENMANAGER_H_ */
