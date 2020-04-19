#include "CompanioBall.h"
#include "SadRobot.h"

const std::string CompanioBall::SPRITE1_PATH = "Ressources/sprite1.png";

CompanioBall::CompanioBall() :
    _ballBody(SPRITE1_PATH, Vector2d(240, 520), _bodyBallSize),
    _eye(SPRITE1_PATH, Vector2d(320, 520), _eyeSize),
    _lightEffects(SPRITE1_PATH, Vector2d(240, 440), _lightEffectsSize)
{
    _ballBody.setParent(this, -1);
    _lightEffects.setParent(this);
    _eye.setParent(this, 2);

    Vector2d spritesPos(-_bodyBallSize.x/2, -_bodyBallSize.y);
    _ballBody.setPosition(spritesPos);
    _lightEffects.setPosition(spritesPos);
    _eye.setPosition(spritesPos);

    _ballBody.setRefPointCentered();
    _eye.setRefPointCentered();
}

void CompanioBall::setSadRobot(SadRobot *sadRobot)
{
    _sadRobot = sadRobot;
}

void CompanioBall::stop()
{
    _lastOrder = ORDER_STOP;
    _timeSinceLastOrder = 0;
    setSpeed(0, 0);
    _ballBody.setRotationSpeed(0);
}

void CompanioBall::go()
{
    _lastOrder = ORDER_GO;
    _timeSinceLastOrder = 0;
}

void CompanioBall::come()
{
    _lastOrder = ORDER_COME;
    _timeSinceLastOrder = 0;
}

void CompanioBall::grab()
{
    stop();
    _lastOrder = ORDER_GRAB;
}

void CompanioBall::buttonPressed(MouseButton::MouseButton, Vector2d mousePos)
{
    if (_lastOrder == ORDER_GRAB) {
        if ( (_ballBody.getAbsolutePosition()-mousePos).getNorm() < _bodyBallSize.x/2 ) {
            _lastOrder = ORDER_GRABED;
        }
    }
}

void CompanioBall::buttonReleased(MouseButton::MouseButton, Vector2d)
{
    if (_lastOrder == ORDER_GRABED) {
        _lastOrder = ORDER_GRAB;
    }
}

int CompanioBall::update(double seconds)
{
    if (_lastOrder == ORDER_GRABED) {
        Vector2d newPos(_mousePosition-_ballBody.getPosition()*getScale());
        if (_sadRobot && (_sadRobot->getBodyAbsolutePosition()-_mousePosition).getNorm() > 120) {
            setPosition(_mousePosition-_ballBody.getPosition()*getScale());
        } else {

        }

    } else if (_lastOrder != ORDER_STOP && _lastOrder != ORDER_GRAB) {
        _timeSinceLastOrder+=seconds;
        if (_timeSinceLastOrder>_orderDuration) {
            if (_sadRobot) {
                _sadRobot->stopBall();
            } else {
                stop();
            }
            stop();
        } else {
            animateMove();
        }
    }
    animateEye(_mousePosition);
    WorldElement::update(seconds);
}

void CompanioBall::animateEye(const Vector2d &target)
{

    Vector2d mouseDir = target-_eye.getAbsolutePosition();
    double angle = mouseDir.getAngleInDegree();
    int bottomDelta = 30;
    if (angle<0) {
        _lastTargetRotation = angle;
    } else if(angle < bottomDelta) {
        _lastTargetRotation = 0;
    } else if(angle > 180 - bottomDelta) {
        _lastTargetRotation = -180;
    }
    _eye.setRotationSpeed(_lastTargetRotation-_eye.getRotation());

}

void CompanioBall::animateMove()
{
    double comeRotationSpeed = 140; // Configurate speed of companion here
    double perimeter = 251.2;
    double comeSpeed = perimeter*comeRotationSpeed/360.;

    Vector2d newSpeed{0, 0};
    double newRotationSpeed = 0;

    if (_sadRobot) {
        if (_sadRobot->getAbsolutePosition().x < getAbsolutePosition().x) {
            comeSpeed = -comeSpeed;
            comeRotationSpeed = -comeRotationSpeed;
        }

        switch(_lastOrder) {
        case ORDER_GO:
            newRotationSpeed = -comeRotationSpeed;
            newSpeed.x = -comeSpeed;
            break;
        case ORDER_COME:
            newRotationSpeed = comeRotationSpeed;
            newSpeed.x = comeSpeed;
            break;
        default:
            break;
        }
    }
    setSpeed(newSpeed);
    _ballBody.setRotationSpeed(newRotationSpeed);

}


