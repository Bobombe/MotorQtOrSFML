
#include "Camera.h"

Camera::Camera()
{
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
/*
#include "moteur2d.h"

Camera::Camera() : _cameraSize(Moteur2D::getInstance()->getScreenSize()), _cameraScale(1)
{

}

Camera::~Camera()
{

}

Vector2d Camera::getCameraPosition()
{
    return _cameraPosition;
}
void Camera::setCameraPosition(Vector2d cameraPosition)
{
    _cameraPosition = cameraPosition;
}

Vector2d Camera::getCameraSize()
{
    return _cameraSize;
}
void Camera::setCameraSize(Vector2d cameraSize)
{
    _cameraSize = cameraSize;
}

double Camera::getCameraScale()
{
    return _cameraScale;
}
void Camera::setCameraScale(double cameraScale)
{
    _cameraScale = cameraScale;
}

void Camera::moveCameraPosition(Vector2d deltaCameraPosition)
{
    _cameraPosition -= deltaCameraPosition;
}
void Camera::moveCameraScale(double deltaCameraScale)
{
    _cameraScale += deltaCameraScale;
}
//*/
