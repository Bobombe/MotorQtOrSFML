
#ifndef SRC_TESTGRAVITY_H_
#define SRC_TESTGRAVITY_H_

#include "Force.h"

class TestGravity : public Force
{
public:
	TestGravity();
	virtual ~TestGravity();

	virtual Vector2d calculateAccelToAdd(WorldElement* we);
};

#endif
