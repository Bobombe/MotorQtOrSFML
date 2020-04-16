#ifndef DEPHAZOR_H
#define DEPHAZOR_H

#include "Sprite.h"

class Dephazor : public Sprite
{
protected:
	bool _dead;
public:
    Dephazor(WorldElement * parent);
    virtual ~Dephazor();

    virtual void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...);

protected:
    virtual int update(double seconds);
};

#endif // DEPHAZOR_H
