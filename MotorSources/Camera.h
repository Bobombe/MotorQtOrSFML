
#ifndef SRC_MOT_CAMERA_H_
#define SRC_MOT_CAMERA_H_

#include "Vector2d.h"
#include "WorldElement.h"
#include "Screen.h"

class Camera : public WorldElement
{
protected:
    double _cameraScale{1};
    Screen* _screen{nullptr};
    WorldElement* _target{nullptr};

public:
    Camera(Screen* s, WorldElement* target);

    double getCameraScale();
    void setCameraScale(double cameraScale);

    virtual void updateCamera();

    // We forbid a camera to have a parent.
    void         setParent(WorldElement *parent, int layer = 0) = delete;

protected:
    int update(double seconds) override;
    int draw() override;

};

#endif
