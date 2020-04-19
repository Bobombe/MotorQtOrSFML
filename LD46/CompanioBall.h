#ifndef COMPANIOBALL_H
#define COMPANIOBALL_H

#include "MouseAndKeyListener.h"
#include "AnimatedSprite.h"
#include "Text.h"

class CompanioBall : public WorldElement, public MouseAndKeyListener
{
protected:
    static const std::string SPRITE1_PATH;

    enum MovementState {
        STANDING_RIGHT = 0,
        STANDING_LEFT,
        MOVING_RIGHT1,
        MOVING_LEFT1
    };

    Vector2d _bodyBallSize{80, 80};
    Vector2d _eyeSize{80, 80};
    Vector2d _lightEffectsSize{80, 40};

    AnimatedSprite _ballBody;
    AnimatedSprite _eye;
    AnimatedSprite _lightEffects;


public:
    CompanioBall();
};

#endif // COMPANIOBALL_H
