
#include "TestGravity.h"

TestGravity::TestGravity()
{
}

TestGravity::~TestGravity()
{
}


Vector2d TestGravity::calculateAccelToAdd(WorldElement*)
{
    return Vector2d(0, 3200);
}
