
#ifndef SRC_STARTSCREEN_H_
#define SRC_STARTSCREEN_H_

#include "Screen.h"
#include "Button.h"

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
