
#ifndef SRC_GAMEMANAGER_H_
#define SRC_GAMEMANAGER_H_

#include "Mot/ScreenManager.h"

class GameManager : public ScreenManager
{

protected:
    int _stateMachine;

public:
    GameManager();
    virtual ~GameManager();

    virtual void update(double seconds);

};

#endif /* SRC_GAMEMANAGER_H_ */
