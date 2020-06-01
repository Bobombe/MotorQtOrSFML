
#include "GPGravity.h"

GPGravity::GPGravity()
{
}

GPGravity::~GPGravity()
{
}


Vector2d GPGravity::calculateAccelToAdd(WorldElement*)
{
    return Vector2d(0, 3200);
}
