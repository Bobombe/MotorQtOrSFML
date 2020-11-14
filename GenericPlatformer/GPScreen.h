
#ifndef SRC_GPScreen_H_
#define SRC_GPScreen_H_

#include "Screen.h"
#include "Button.h"

class GPScreen : public Screen
{
protected:
    Button _bt;
public:
    GPScreen();
    virtual ~GPScreen();

protected:
    virtual int draw();
    void addPlatform(int posx, int posy, int width, int hight=1);
};

#endif /* SRC_GPScreen_H_ */
