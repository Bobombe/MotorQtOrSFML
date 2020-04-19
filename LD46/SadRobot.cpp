#include "SadRobot.h"

const std::string SadRobot::SPRITE1_PATH = "Ressources/sprite1.png";

SadRobot::SadRobot() :
    _leftLeg(SPRITE1_PATH, Vector2d(488, 581), _leftLegSize),
    _rightLeg(SPRITE1_PATH, Vector2d(527, 581), _rightLegSize),
    _textBackground(SPRITE1_PATH, Vector2d(570, 468), _textBackgroundSize),
    _body(SPRITE1_PATH, Vector2d(480, 456), _bodySize),
    _head(SPRITE1_PATH, Vector2d(500, 400), _headSize),
    _eye(SPRITE1_PATH, Vector2d(543, 411), _eyeSize),
    _leftHat(SPRITE1_PATH, Vector2d(495, 360), _leftHatSize),
    _rightHat(SPRITE1_PATH, Vector2d(520, 360), _rightHatSize),
    _graber(SPRITE1_PATH, Vector2d(600, 240), _graberSize)
{

    _leftLeg.setParent(this);_leftLeg.setPosition(_leftLegStartPos);
    _rightLeg.setParent(this);_rightLeg.setPosition(_rightLegStartPos);
    _bodyAndText.setParent(this);_bodyAndText.setPosition(_bodyStartPos);
    _body.setParent(&_bodyAndText);_body.setRefPoint(Vector2d(40, 0));_body.setPosition(0, 0);
    _head.setParent(&_body);_head.setRefPoint(Vector2d(20, 0));_head.setPosition(0, -40+4);
    _eye.setParent(&_head);_eye.setRefPoint(Vector2d(2, 2));_eye.setPosition(_eyeStartPos);
    _leftHat.setParent(&_head);_leftHat.setRefPoint(Vector2d(24, 0));_leftHat.setPosition(_leftHatStartPos);
    _rightHat.setParent(&_head);_rightHat.setPosition(_rightHatStartPos);
    _graber.setParent(&_head);_graber.setRefPoint(Vector2d(134, 50));_graber.setPosition(0, 0);
    _graber.setVisible(false);

    _textBackground.setParent(&_bodyAndText, -1);
    _textBackground.setRefPointCentered();
    _textBackground.setPosition(_textBackgroundStartPos);
    _text.setParent(&_textBackground);
    _text.setCharacterSize(16);
    _text.setColor(Text::Black);
    setText("Hello...");

}

void SadRobot::setText(std::string text)
{
    _text.setText(text);
    _text.setRefPointCentered();
    _text.setPosition(0, -3);
}

void SadRobot::mouseMoved(Vector2d pos)
{
    _mousePos = pos;
}

void SadRobot::keyPressed(Key::Key key)
{
    if (key == Key::Left || key == Key::S) {
        _movingLeft= true;
    } else if (key == Key::Right || key == Key::F) {
        _movingRight= true;
    } else if (key == Key::Up || key == Key::E) {
        _jump = true;
    } else if (key == Key::Down || key == Key::D) {
        _sitting = true;
    }
}
void SadRobot::keyReleased(Key::Key key)
{
    if (key == Key::Left || key == Key::S) {
        _movingLeft= false;
    } else if (key == Key::Right || key == Key::F) {
        _movingRight= false;
    } else if (key == Key::Up || key == Key::E) {
        _jump = false;
    } else if (key == Key::Down || key == Key::D) {
        _sitting = false;
    }
}

int SadRobot::update(double seconds)
{
    /////////////////////////////////////////
   //       DEPLACEMENTS HORIZONTAUX      //
  /////////////////////////////////////////
    if (_sitting && !_jump && _onGround) {
        _state = SEATING;
    } else if (_movingRight && !_movingLeft) {

        if(_onGround) {
            _state = MOVING_RIGHT1;
        }
    } else if (_movingLeft && !_movingRight) {

        if(_onGround) {
            _state = MOVING_LEFT1;
        }
    } else { // Slowing
        if (_state == MOVING_LEFT1) {
            _state = STANDING_LEFT;
        } else {
            _state = STANDING_RIGHT;
        }
    }
    switch (_state) {
    case MOVING_LEFT1:
        animateMoovingLeft();
        animateSeating(false);
        animateEye(_mousePos);
        break;
    case MOVING_RIGHT1:
        animateMoovingRight();
        animateSeating(false);
        animateEye(_mousePos);
        break;
    case SEATING:
        animateSeating();
        animateStopMooving();
        _eye.setPosition(0, _eyeStartPos.y);
        break;
    default:
        animateStopMooving();
        animateSeating(false);
        animateEye(_mousePos);
        break;
    }
    WorldElement::update(seconds);

    return 0;
}

void SadRobot::animateMoovingLeft()
{
    double legTopPosition = _rightLegStartPos.y-_deltaLegHight;
    double leftLandingZone = _leftLegStartPos.x + _deltaLandingZone;

    Vector2d nextSpeedLeftLeg{0, 0};
    Vector2d nextSpeedRightLeg{0, 0};

    Vector2d rightLegPos(_rightLeg.getPosition());
    Vector2d leftLegPos(_leftLeg.getPosition());

    // if right isn't lifted, we began the walk with left
    if (rightLegPos.y < _rightLegStartPos.y) {
        // moving the right leg to the left on top

        // Horizontal movements of Right leg
        if (rightLegPos.x < _leftLegStartPos.x) {
            // End of horizontal movement
            rightLegPos.x = _leftLegStartPos.x;
            _rightLeg.setPosition(rightLegPos);
        } else if (rightLegPos.x > _leftLegStartPos.x) {
            nextSpeedRightLeg.x = -_baseSpeed;
        }
        // Horizontal movements of Left leg
        if (leftLegPos.x > _rightLegStartPos.x) {
            leftLegPos.x = _rightLegStartPos.x;
            _leftLeg.setPosition(leftLegPos);
        } else if (leftLegPos.x < _rightLegStartPos.x) {
            nextSpeedLeftLeg.x = _baseSpeed;
        }


        if (rightLegPos.y > legTopPosition) {
            // Leg going up
            nextSpeedRightLeg.y = -_baseSpeed/2;
        }
        if (rightLegPos.x < leftLandingZone) {
            nextSpeedRightLeg.y = _baseSpeed/2;
        }
        setSpeed(-nextSpeedLeftLeg);

    } else if (leftLegPos.y < _leftLegStartPos.y) {
        // moving the left leg to the left on top

        // Horizontal movements of Left leg
        if (leftLegPos.x < _leftLegStartPos.x) {
            // End of horizontal movement
            leftLegPos.x = _leftLegStartPos.x;
            _leftLeg.setPosition(leftLegPos);
        } else if (leftLegPos.x > _leftLegStartPos.x) {
            nextSpeedLeftLeg.x = -_baseSpeed;
        }
        // Horizontal movements of Right leg
        if (rightLegPos.x > _rightLegStartPos.x) {
            rightLegPos.x = _rightLegStartPos.x;
            _rightLeg.setPosition(rightLegPos);
        } else if (rightLegPos.x < _rightLegStartPos.x) {
            nextSpeedRightLeg.x = _baseSpeed;
        }

        if (leftLegPos.y > legTopPosition) {
            // Leg going up
            nextSpeedLeftLeg.y = -_baseSpeed/2;
        }
        if (leftLegPos.x < leftLandingZone) {
            nextSpeedLeftLeg.y = _baseSpeed/2;
        }
        setSpeed(-nextSpeedRightLeg);

    } else if (leftLegPos.x < rightLegPos.x) {
        nextSpeedRightLeg.y = -_baseSpeed/2;
    } else {
        nextSpeedLeftLeg.y = -_baseSpeed/2;
    }
    _leftLeg.setSpeed(nextSpeedLeftLeg);
    _rightLeg.setSpeed(nextSpeedRightLeg);
}

void SadRobot::animateMoovingRight()
{
    double legTopPosition = _rightLegStartPos.y-_deltaLegHight;
    double rightLandingZone = _rightLegStartPos.x - _deltaLandingZone;

    Vector2d nextSpeedLeftLeg{0, 0};
    Vector2d nextSpeedRightLeg{0, 0};

    Vector2d rightLegPos(_rightLeg.getPosition());
    Vector2d leftLegPos(_leftLeg.getPosition());

    // if right is lifted, we began the walk with it
    if (rightLegPos.y < _rightLegStartPos.y) {
        // moving the right leg to the right on top

        // Horizontal movements of Left leg
        if (leftLegPos.x < _leftLegStartPos.x) {
            // End of horizontal movement
            leftLegPos.x = _leftLegStartPos.x;
            _leftLeg.setPosition(leftLegPos);
        } else if (leftLegPos.x > _leftLegStartPos.x) {
            nextSpeedLeftLeg.x = -_baseSpeed;
        }
        // Horizontal movements of Left leg
        if (rightLegPos.x > _rightLegStartPos.x) {
            rightLegPos.x = _rightLegStartPos.x;
            _rightLeg.setPosition(rightLegPos);
        } else if (rightLegPos.x < _rightLegStartPos.x) {
            nextSpeedRightLeg.x = _baseSpeed;
        }


        if (rightLegPos.y > legTopPosition) {
            // Leg going up
            nextSpeedRightLeg.y = -_baseSpeed/2;
        }
        if (rightLegPos.x > rightLandingZone) {
            // Landing
            nextSpeedRightLeg.y = _baseSpeed/2;
        }
        setSpeed(-nextSpeedLeftLeg);

    } else if (leftLegPos.y < _leftLegStartPos.y) {
        // moving the left leg to the right on top

        // Horizontal movements of Right leg
        if (rightLegPos.x < _leftLegStartPos.x) {
            // End of horizontal movement
            rightLegPos.x = _leftLegStartPos.x;
            _rightLeg.setPosition(rightLegPos);
        } else if (rightLegPos.x > _leftLegStartPos.x) {
            nextSpeedRightLeg.x = -_baseSpeed;
        }
        // Horizontal movements of Left leg
        if (leftLegPos.x > _rightLegStartPos.x) {
            leftLegPos.x = _rightLegStartPos.x;
            _leftLeg.setPosition(leftLegPos);
        } else if (leftLegPos.x < _rightLegStartPos.x) {
            nextSpeedLeftLeg.x = _baseSpeed;
        }

        if (leftLegPos.y > legTopPosition) {
            // Leg going up
            nextSpeedLeftLeg.y = -_baseSpeed/2;
        }
        if (leftLegPos.x > rightLandingZone) {
            nextSpeedLeftLeg.y = _baseSpeed/2;
        }
        setSpeed(-nextSpeedRightLeg);

    } else if (leftLegPos.x < rightLegPos.x) {
        nextSpeedLeftLeg.y = -_baseSpeed/2;
    } else {
        nextSpeedRightLeg.y = -_baseSpeed/2;
    }
    _leftLeg.setSpeed(nextSpeedLeftLeg);
    _rightLeg.setSpeed(nextSpeedRightLeg);

}

void SadRobot::animateStopMooving()
{
    Vector2d nextSpeedLeftLeg{0, 0};
    Vector2d nextSpeedRightLeg{0, 0};

    Vector2d rightLegPos(_rightLeg.getPosition());
    Vector2d leftLegPos(_leftLeg.getPosition());

    if (leftLegPos.x <= rightLegPos.x) {
        // Left leg goes to left and Right leg to right
        if (leftLegPos.x < _leftLegStartPos.x) {
            // End of horizontal movement
            leftLegPos.x = _leftLegStartPos.x;
            _leftLeg.setPosition(leftLegPos);
        } else if (leftLegPos.x > _leftLegStartPos.x) {
            nextSpeedLeftLeg.x = -_baseSpeed;
        }
        if (rightLegPos.x > _rightLegStartPos.x) {
            rightLegPos.x = _rightLegStartPos.x;
            _rightLeg.setPosition(rightLegPos);
        } else if (rightLegPos.x < _rightLegStartPos.x) {
            nextSpeedRightLeg.x = _baseSpeed;
        }
    } else {
        // Right leg goes to left and Left leg to right
        if (rightLegPos.x < _leftLegStartPos.x) {
            // End of horizontal movement
            rightLegPos.x = _leftLegStartPos.x;
            _rightLeg.setPosition(rightLegPos);
        } else if (rightLegPos.x > _leftLegStartPos.x) {
            nextSpeedRightLeg.x = -_baseSpeed;
        }
        if (leftLegPos.x > _rightLegStartPos.x) {
            leftLegPos.x = _rightLegStartPos.x;
            _leftLeg.setPosition(leftLegPos);
        } else if (leftLegPos.x < _rightLegStartPos.x) {
            nextSpeedLeftLeg.x = _baseSpeed;
        }
    }
    //Going down
    if (leftLegPos.y < _leftLegStartPos.y) {
        nextSpeedLeftLeg.y = _baseSpeed/2;
    } else if (leftLegPos.y > _leftLegStartPos.y) {
        leftLegPos.y = _leftLegStartPos.y;
        _leftLeg.setPosition(leftLegPos);
    }
    if (rightLegPos.y < _rightLegStartPos.y) {
        nextSpeedRightLeg.y = _baseSpeed/2;
    } else if (rightLegPos.y > _rightLegStartPos.y) {
        rightLegPos.y = _rightLegStartPos.y;
        _rightLeg.setPosition(rightLegPos);
    }

    _leftLeg.setSpeed(nextSpeedLeftLeg);
    _rightLeg.setSpeed(nextSpeedRightLeg);
    setSpeed(0, 0);
}

void SadRobot::animateEye(Vector2d const & target)
{
    Vector2d newPos(0, _eyeStartPos.y);
    Vector2d mouseDir = target-_eye.getAbsolutePosition();
    double angle = mouseDir.getAngleInDegree();
    if (angle>0) angle = -angle; // Negative of absolute value between -180 and 0
    angle = angle/180.*(2*_eyeStartPos.x-1) +_eyeStartPos.x-1; // we got a value between -_eyeStartPos.x+1 and +_eyeStartPos.x

    double norm = mouseDir.getNorm();
    int normLimite = 20;
    if (norm > normLimite) {
        newPos.x = angle;
    } else {
        double targetPos = mouseDir.x+_eye.getPosition().x;
        if (targetPos > _eyeStartPos.y) {
            targetPos = _eyeStartPos.y;
        } else if (targetPos < -_eyeStartPos.y) {
            targetPos = -_eyeStartPos.y;
        }
        double ratio = norm*norm/(normLimite*normLimite);
        newPos.x = angle*ratio + targetPos*(1-ratio);
    }
    _eye.setPosition(newPos);

}

void SadRobot::animateSeating(bool seating)
{
    Vector2d newBodySpeed(0, 0);
    Vector2d bodyPos(_bodyAndText.getPosition());
    double diffBodyHeightWhileSeating = 15;
    double seatingSpeed = _baseSpeed / 4;

    if (!seating) {
        if (bodyPos.y>_bodyStartPos.y) {
            newBodySpeed.y = -seatingSpeed;
        } else if (bodyPos.y<_bodyStartPos.y) {
            bodyPos.y = _bodyStartPos.y;
            _bodyAndText.setPosition(bodyPos);
        }
    } else {
        if (bodyPos.y<_bodyStartPos.y+diffBodyHeightWhileSeating) {
            newBodySpeed.y = seatingSpeed;
        } else if (bodyPos.y>_bodyStartPos.y+diffBodyHeightWhileSeating) {
            bodyPos.y = _bodyStartPos.y+diffBodyHeightWhileSeating;
            _bodyAndText.setPosition(bodyPos);
        }
    }
    _bodyAndText.setSpeed(newBodySpeed);

    // Opening hat
    if (_grabBallActivated) {
        Vector2d leftHatPos(_leftHat.getPosition());

        Vector2d rightHatMove(5, 5);
        Vector2d leftHatMove(-rightHatMove.x, rightHatMove.y);

        Vector2d rightOpenHatPos(_leftHatStartPos+rightHatMove);
        Vector2d leftOpenHatPos(_rightHatStartPos+leftHatMove);

        rightHatMove.normalize(); rightHatMove*=seatingSpeed/2;
        leftHatMove.normalize(); leftHatMove*=seatingSpeed/2;

        if (!seating) {
            if (leftHatPos.x < _leftHatStartPos.x) { // check on one size, but moove both.
                _leftHat.setSpeed(-leftHatMove);
                _rightHat.setSpeed(-rightHatMove);
                _graber.setVisible(false);
            } else if (leftHatPos.x > _leftHatStartPos.x) {
                _leftHat.setPosition(_leftHatStartPos);
                _rightHat.setPosition(_rightHatStartPos);
                _leftHat.setSpeed(0, 0);
                _rightHat.setSpeed(0, 0);
            }
        } else {
            if (leftHatPos.x > leftOpenHatPos.x) { // check on one size, but moove both.
                _leftHat.setSpeed(leftHatMove);
                _rightHat.setSpeed(rightHatMove);
            } else if (leftHatPos.x < leftOpenHatPos.x) {
                _leftHat.setPosition(leftOpenHatPos);
                _rightHat.setPosition(rightOpenHatPos);
                _leftHat.setSpeed(0, 0);
                _rightHat.setSpeed(0, 0);
                _graber.setVisible(true);
            }
        }

    }
}
