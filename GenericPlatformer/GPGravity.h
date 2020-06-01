
#ifndef SRC_GPGravity_H_
#define SRC_GPGravity_H_

#include "Force.h"

class GPGravity : public Force
{
public:
    GPGravity();
    virtual ~GPGravity();

	virtual Vector2d calculateAccelToAdd(WorldElement* we);
};

#endif
