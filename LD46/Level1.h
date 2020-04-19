#ifndef LEVEL1_H
#define LEVEL1_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"

#include "SadRobot.h"
#include "CompanioBall.h"

class Level1: public Screen
{
protected:
    SadRobot _sadRobot;
    CompanioBall _companioBall;

public:
    Level1();
    virtual ~Level1();

    void initScreen() override;

protected:
    virtual int draw();
};
#endif // LEVEL1_H
