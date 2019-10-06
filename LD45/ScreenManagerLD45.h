
#ifndef SRC_ScreenManagerLD45_H_
#define SRC_ScreenManagerLD45_H_

#include "ScreenManager.h"
#include "Player.h"

class ScreenManagerLD45 : public ScreenManager
{

protected:
    int _stateMachine;
    Player _player;

public:
    ScreenManagerLD45();
    virtual ~ScreenManagerLD45();

    virtual void update(double seconds, int updateReturn, int drawReturn);

};

#endif /* SRC_ScreenManagerLD45_H_ */
