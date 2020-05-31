
#ifndef Launcher_LauncherScreenManager_H_
#define Launcher_LauncherScreenManager_H_

#include "ScreenManager.h"

class LauncherScreenManager : public ScreenManager
{

protected:
    int _stateMachine;

public:
    LauncherScreenManager();
    virtual ~LauncherScreenManager();

    virtual void update(double seconds, int updateReturn, int drawReturn);

};

#endif /* Launcher_LauncherScreenManager_H_ */
