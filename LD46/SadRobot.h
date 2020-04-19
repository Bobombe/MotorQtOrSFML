#ifndef SADROBOT_H
#define SADROBOT_H

#include "MouseAndKeyListener.h"
#include "AnimatedSprite.h"
#include "Text.h"

class SadRobot : public WorldElement, public MouseAndKeyListener
{
protected:
    static const std::string SPRITE1_PATH;

    enum MovementState {
        STANDING_RIGHT = 0,
        STANDING_LEFT,
        MOVING_RIGHT1,
        MOVING_RIGHT2,
        MOVING_LEFT1,
        MOVING_LEFT2,
        SEATING,
        SEATED,
        JETING
    };

    // Size of parts
    Vector2d _leftLegSize{25, 19};
    Vector2d _rightLegSize{25, 19};
    Vector2d _textBackgroundSize{60, 24};
    Vector2d _bodySize{80, 104};
    Vector2d _headSize{40, 40};
    Vector2d _eyeSize{5, 5};
    Vector2d _leftHatSize{25, 19};
    Vector2d _rightHatSize{25, 19};
    Vector2d _graberSize{268, 194};

    // Starting relative position
    Vector2d _leftLegStartPos{-25-7, -19+3};
    Vector2d _rightLegStartPos{7, -19+3};
    Vector2d _bodyStartPos{0, -104-19+5};
    Vector2d _textBackgroundStartPos{0, 24};
    Vector2d _eyeStartPos{16, 13};
    Vector2d _leftHatStartPos{-1, -19+6};
    Vector2d _rightHatStartPos{0, -19+6};

    // Robot's part
    AnimatedSprite _leftLeg;
    AnimatedSprite _rightLeg;
    Sprite _textBackground;
    AnimatedSprite _body;
    AnimatedSprite _head;
    AnimatedSprite _eye;
    AnimatedSprite _leftHat;
    AnimatedSprite _rightHat;
    AnimatedSprite _graber;
    Text _text;
    WorldElement _bodyAndText;

    Vector2d _mousePos;

    // For movement
    MovementState _state{STANDING_RIGHT};
    bool _movingLeft{false};
    bool _movingRight{false};
    bool _jump{false};
    bool _sitting{false};

    bool _onGround{true};
    double _groundPosition{0}; // Store the y position when on ground

    // Physics data of character
    int _baseSpeed{100};
    int _deltaLandingZone{12};
    int _deltaLegHight{10};


    // Powers
    bool _grabBallActivated{true};

public:
    SadRobot();
    void setText(std::string text);


    void mouseMoved(Vector2d pos) override;
    void keyPressed(Key::Key key) override;
    void keyReleased(Key::Key key) override;


protected:
    int update(double seconds) override;
    //int draw() override;

    void animateMoovingLeft();
    void animateMoovingRight();
    void animateStopMooving();
    void animateEye(const Vector2d &target);
    void animateSeating(bool seating = true);
};

#endif // SADROBOT_H
