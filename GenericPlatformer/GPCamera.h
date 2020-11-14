#ifndef GPCAMERA_H
#define GPCAMERA_H

#include "Camera.h"

class GPCamera : public Camera
{
public:
    GPCamera(Screen *s, WorldElement *target);

    void updateCamera() override;
};

#endif // GPCAMERA_H
