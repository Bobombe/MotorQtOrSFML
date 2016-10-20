
#ifndef SRC_STARTSCREEN_H_
#define SRC_STARTSCREEN_H_

#include "Mot/Screen.h"

class StartScreen : public Screen
{
public:
    StartScreen();
    virtual ~StartScreen();

    virtual int draw(Vector2d pos = Vector2d());
};

#endif /* SRC_STARTSCREEN_H_ */
