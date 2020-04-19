#include "CompanioBall.h"

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
