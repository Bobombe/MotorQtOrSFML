
#ifndef SRC_SCREENMANAGERTEST_H_
#define SRC_SCREENMANAGERTEST_H_

#include "ScreenManager.h"
#include "LD46/TitleScreen.h"
#include "LD46/Level1.h"

class ScreenManagerTest : public ScreenManager
{

protected:
    int _stateMachine;

    tu::TitleScreen* _titleScreen{nullptr};
    Level1* _level1{nullptr};

public:
    ScreenManagerTest();
    virtual ~ScreenManagerTest();

    void update(double seconds, int updateReturn, int drawReturn) override;

    void startScreen(int screenId, Screen* screen);

};

#endif /* SRC_SCREENMANAGERTEST_H_ */
