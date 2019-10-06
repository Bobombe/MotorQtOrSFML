#include "BaseAnimatedSprite.h"

BaseAnimatedSprite::BaseAnimatedSprite() : AnimatedSprite("Ressources/BaseCharacter.png"), _subSize(32, 32)
{
    defineAnimations();
    _collider = new Collider(this);
    _collider->initRectangular(7, _subSize.y/3., _subSize.x-14, 2*_subSize.y/3.);
}

BaseAnimatedSprite::BaseAnimatedSprite(std::string texturePath) : AnimatedSprite(texturePath), _subSize(32, 32)
{
    defineAnimations();
    _collider = new Collider(this);
    _collider->initRectangular(7, _subSize.y/3., _subSize.x-14, 2.*_subSize.y/3.);
}

void BaseAnimatedSprite::defineAnimations()
{
    addAnimationStep(STAY_STILL_FRONT, 1, 0);
    addAnimationStep(STAY_STILL_LEFT, 1, 1);
    addAnimationStep(STAY_STILL_RIGHT, 1, 2);
    addAnimationStep(STAY_STILL_BACK, 1, 3);

    addAnimationStep(WALK_FRONT, 1, 0);
    addAnimationStep(WALK_FRONT, 0, 0);
    addAnimationStep(WALK_FRONT, 1, 0);
    addAnimationStep(WALK_FRONT, 2, 0);

    addAnimationStep(WALK_LEFT, 1, 1);
    addAnimationStep(WALK_LEFT, 0, 1);
    addAnimationStep(WALK_LEFT, 1, 1);
    addAnimationStep(WALK_LEFT, 2, 1);

    addAnimationStep(WALK_RIGHT, 1, 2);
    addAnimationStep(WALK_RIGHT, 0, 2);
    addAnimationStep(WALK_RIGHT, 1, 2);
    addAnimationStep(WALK_RIGHT, 2, 2);

    addAnimationStep(WALK_BACK, 1, 3);
    addAnimationStep(WALK_BACK, 0, 3);
    addAnimationStep(WALK_BACK, 1, 3);
    addAnimationStep(WALK_BACK, 2, 3);

    addAnimationStep(FIGHT_FRONT, 1, 0);
    addAnimationStep(FIGHT_FRONT, 3, 0);

    addAnimationStep(FIGHT_LEFT, 1, 1);
    addAnimationStep(FIGHT_LEFT, 3, 1);

    addAnimationStep(FIGHT_RIGHT, 1, 2);
    addAnimationStep(FIGHT_RIGHT, 3, 2);

    addAnimationStep(FIGHT_BACK, 1, 3);
    addAnimationStep(FIGHT_BACK, 3, 3);

    int walkFPS = 4;
    int fightFPS = 2;
    setFramePerSecs(WALK_FRONT, walkFPS);
    setFramePerSecs(WALK_LEFT, walkFPS);
    setFramePerSecs(WALK_RIGHT, walkFPS);
    setFramePerSecs(WALK_BACK, walkFPS);
    setFramePerSecs(FIGHT_FRONT, fightFPS);
    setFramePerSecs(FIGHT_LEFT, fightFPS);
    setFramePerSecs(FIGHT_RIGHT, fightFPS);
    setFramePerSecs(FIGHT_BACK, fightFPS);
}

void BaseAnimatedSprite::addAnimationStep(int annimationId, int column, int row)
{
    addSubRect(annimationId, Rectangle(_subSize.x*column, _subSize.x*row, _subSize.x, _subSize.y));
}
