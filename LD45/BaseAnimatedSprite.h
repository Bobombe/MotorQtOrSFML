#ifndef BASEANIMATEDSPRITE_H
#define BASEANIMATEDSPRITE_H

#include "AnimatedSprite.h"
#include "Collider.h"

class BaseAnimatedSprite : public AnimatedSprite
{
protected:
    enum AnimationId {
        STAY_STILL_FRONT=0,
        STAY_STILL_LEFT,
        STAY_STILL_RIGHT,
        STAY_STILL_BACK,
        WALK_FRONT,
        WALK_LEFT,
        WALK_RIGHT,
        WALK_BACK,
        FIGHT_FRONT,
        FIGHT_LEFT,
        FIGHT_RIGHT,
        FIGHT_BACK
    };

public:
    BaseAnimatedSprite();
    BaseAnimatedSprite(std::string texturePath);

protected:
    void defineAnimations();
    void addAnimationStep(int annimationId, int column, int row);

private:
    Vector2d _subSize;
};

#endif // BASEANIMATEDSPRITE_H
