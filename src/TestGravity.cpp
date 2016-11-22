
#include "TestGravity.h"

TestGravity::TestGravity()
{
}

TestGravity::~TestGravity()
{
}


Vector2d TestGravity::calculateAccelToAdd(WorldElement* we)
{
	if (we->getPosition().y < 500) {
		return Vector2d(0, 1000);
	} else {
		return Vector2d(0, -1000);
	}
}
