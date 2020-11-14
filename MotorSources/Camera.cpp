
#include "Camera.h"

Camera::Camera(Screen *s, WorldElement *target) : _screen{s}, _target{target}
{
    setSize(_screen->getSize());
    _weName = "Camera";
}

double Camera::getCameraScale()
{
    return _cameraScale;
}
void Camera::setCameraScale(double cameraScale)
{
    _cameraScale = cameraScale;
}

void Camera::updateCamera()
{
    Vector2d pos = _target->getAbsolutePosition();
    pos.x-=getSize().x/10.;
    pos.y-=getSize().y/2.;
    setPosition(pos);
}

int Camera::update(double seconds)
{
    int ret = WorldElement::update(seconds);
    updateCamera();
    return ret;
}

int Camera::draw()
{
    int ret = WorldElement::draw();
    return ret;
}
