
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
    /**
     * \param seconds : time elapsed since last frame.
     * \param updateReturn value returned by currentScreen after its update phase.
     * \param drawReturn value returned by currentScreen after its draw phase.
     *
     * This must be reimplemented in a sub class to manage the game. It is called just after the current screen was drawn.
     * It can be used to change the _currentScreen for next frame while managing a state machine for example...
     */
    virtual void update(double seconds, int updateReturn, int drawReturn)=0;

    void addScreen(int screenId, Screen* s);
    void deleteScreen(int screenId);

    Screen* screenAt(int indexOfScreen);
    Screen* getCurrentScreen();
    int getCurrentScreenId();
    void setCurrentScreenId(int screenId);

};

#endif /* SRC_MOT_SCREENMANAGER_H_ */
