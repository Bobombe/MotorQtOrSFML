
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

    virtual int draw(Vector2d pos = Vector2d());
};

#endif /* SRC_STARTSCREEN_H_ */
