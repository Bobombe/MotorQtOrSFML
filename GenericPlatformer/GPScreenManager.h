
#ifndef SRC_GPScreenManager_H_
#define SRC_GPScreenManager_H_

#include "ScreenManager.h"

class GPScreenManager : public ScreenManager
{

protected:
    int _stateMachine;

public:
    GPScreenManager();
    virtual ~GPScreenManager();

    virtual void update(double seconds, int updateReturn, int drawReturn);

};

#endif /* SRC_GPScreenManager_H_ */
