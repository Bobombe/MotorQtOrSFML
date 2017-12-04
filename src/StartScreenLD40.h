
#ifndef SRC_STARTSCREENLD40_H_
#define SRC_STARTSCREENLD40_H_

#include "Mot/Screen.h"
#include "Mot/Button.h"

class StartScreenLD40 : public Screen
{
protected:
    Button _btStart;
public:
    StartScreenLD40();
    virtual ~StartScreenLD40();

protected:
    virtual int draw();
};

#endif /* SRC_STARTSCREEN_H_ */