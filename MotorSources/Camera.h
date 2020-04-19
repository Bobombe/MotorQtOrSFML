
#ifndef SRC_MOT_CAMERA_H_
#define SRC_MOT_CAMERA_H_

#include "Vector2d.h"
#include "WorldElement.h"

class Camera : public WorldElement
{
protected:
    double _cameraScale{1};

public:
    Camera();

    double getCameraScale();
    void setCameraScale(double cameraScale);
    /*
protected:
    Vector2d _cameraPosition;
    Vector2d _cameraSize;
    double _cameraScale;

public:
    Camera();
    virtual ~Camera();

    Vector2d getCameraPosition();
    void setCameraPosition(Vector2d cameraPosition);

    Vector2d getCameraSize();
    void setCameraSize(Vector2d cameraSize);

    double getCameraScale();
    void setCameraScale(double cameraScale);

    void moveCameraPosition(Vector2d deltaCameraPosition);
    void moveCameraScale(double deltaCameraScale);//*/
};

#endif
