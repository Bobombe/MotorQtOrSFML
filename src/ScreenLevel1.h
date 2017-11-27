
#ifndef SRC_SCREENLEVEL1_H_
#define SRC_SCREENLEVEL1_H_

#include "Mot/Screen.h"

class ScreenLevel1 : public Screen
{
protected:
    bool _zoomin;

public:
    ScreenLevel1();
    virtual ~ScreenLevel1();
protected:
    virtual int update(double seconds);
};

#endif
