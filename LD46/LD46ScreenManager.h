
#ifndef SRC_LD46SCREENMANAGER_H_
#define SRC_LD46SCREENMANAGER_H_

#include "ScreenManager.h"
#include "LD46/LD46TitleScreen.h"
#include "LD46/Level1.h"

class LD46ScreenManager : public ScreenManager
{

protected:
    int _stateMachine;

    LD46TitleScreen* _titleScreen{nullptr};
    Level1* _level1{nullptr};

public:
    LD46ScreenManager();
    virtual ~LD46ScreenManager() override;

    void update(double seconds, int updateReturn, int drawReturn) override;

    void startScreen(int screenId, Screen* screen);

};

#endif /* SRC_LD46SCREENMANAGER_H_ */
