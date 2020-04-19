#ifndef COMPANIOBALL_H
#define COMPANIOBALL_H

#include "MouseAndKeyListener.h"
#include "AnimatedSprite.h"
#include "Text.h"

class SadRobot;
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

    enum ORDERS {
        ORDER_NONE,
        ORDER_STOP,
        ORDER_GO,
        ORDER_COME,
        ORDER_GRAB,
        ORDER_GRABED
    };

    double _lastTargetRotation {0};

    Vector2d _bodyBallSize{80, 80};
    Vector2d _eyeSize{80, 80};
    Vector2d _lightEffectsSize{80, 40};

    AnimatedSprite _ballBody;
    AnimatedSprite _eye;
    AnimatedSprite _lightEffects;

    // Orders
    ORDERS _lastOrder{ORDER_STOP};
    SadRobot* _sadRobot{nullptr};
    int _orderDuration{10};
    double _timeSinceLastOrder{0};


public:
    CompanioBall();

    // Orders
    void setSadRobot(SadRobot* sadRobot);
    void stop();
    void go();
    void come();
    void grab();

    void buttonPressed(MouseButton::MouseButton, Vector2d mousePos) override;
    void buttonReleased(MouseButton::MouseButton, Vector2d) override;

protected:
    int update(double seconds) override;

    void animateEye(const Vector2d &target);
    void animateMove();

};

#endif // COMPANIOBALL_H
