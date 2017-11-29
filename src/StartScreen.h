
#ifndef SRC_STARTSCREEN_H_
#define SRC_STARTSCREEN_H_

#include "Mot/Screen.h"
#include "Mot/Button.h"

class StartScreen : public Screen
{
protected:
    Button _bt;
public:
    StartScreen();
    virtual ~StartScreen();

protected:
    virtual int draw();
};

#endif /* SRC_STARTSCREEN_H_ */
