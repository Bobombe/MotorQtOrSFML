
#ifndef SRC_SCREENMANAGERTEST_H_
#define SRC_SCREENMANAGERTEST_H_

#include "ScreenManager.h"

class ScreenManagerTest : public ScreenManager
{

protected:
    int _stateMachine;

public:
    ScreenManagerTest();
    virtual ~ScreenManagerTest();

    virtual void update(double seconds, int updateReturn, int drawReturn);

};

#endif /* SRC_SCREENMANAGERTEST_H_ */
