#include "GPCamera.h"

GPCamera::GPCamera(Screen *s, WorldElement *target) : Camera(s, target)
{

}

void GPCamera::updateCamera()
{
    Vector2d move{0, 0};// result

    //Configuration
    float margin = 4;

    //Entry data
    Vector2d targetPos(_target->getAbsolutePosition());
    Vector2d targetSize(_target->getAbsoluteSize());
    Vector2d size(getSize());

    //Calculation
    if (targetPos.x < size.x/margin) {
        move.x = targetPos.x - size.x/margin;
    }
    if (targetPos.x+targetSize.x > size.x*(margin-1)/margin) {
        move.x = targetPos.x+targetSize.x - size.x*(margin-1)/margin;
    }
    if (targetPos.y < size.y/margin) {
        move.y = targetPos.y - size.y/margin;
    }
    if (targetPos.y+targetSize.y > size.y*(margin-1)/margin) {
        move.y = targetPos.y+targetSize.y - size.y*(margin-1)/margin;
    }

    setPosition(move);
}
