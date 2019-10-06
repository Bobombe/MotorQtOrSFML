#include "BaseCharacter.h"
#include "Equipment.h"
#include "moteur2d.h"

BaseCharacter::BaseCharacter() : BaseAnimatedSprite()
{
    //setScale(2);
}
int BaseCharacter::update(double seconds)
{
    int ret = 0;

    // Setting new speed
    int absSpeed = 80;
    Vector2d newSpeed;
    if (_down) {
        newSpeed.y += absSpeed;
    }
    if (_left) {
        newSpeed.x -= absSpeed;
    }
    if (_right) {
        newSpeed.x += absSpeed;
    }
    if (_up) {
        newSpeed.y -= absSpeed;
    }
    setSpeed(newSpeed);
    ret = AnimatedSprite::update(seconds);

    return ret;
}


void BaseCharacter::handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int ...)
{
    if (weColided->getWeName() == "Obstacle") {
        double offcet = 0.01;
        Vector2d newPos = getPosition();
        Vector2d newSpeed = getSpeed();
        // Vector2d oldPos = getPosition() - (getSpeed()*secsSinceLastFrame);

        Vector2d posCh = getCollider()->getPos();
        Vector2d posOb = weColided->getCollider()->getPos();

        Vector2d sizeCh = getCollider()->getSize();
        Vector2d sizeOb = weColided->getCollider()->getSize();

        Vector2d deltaPosCharaCollider = posCh - newPos;

        double RL = posOb.x - (posCh.x + sizeCh.x);
        double UD = posCh.y - (posOb.y + sizeOb.y);
        double LR = posCh.x - (posOb.x + sizeOb.x);
        double DU = posOb.y - (posCh.y + sizeCh.y);

        if (RL > UD && RL > LR && RL > DU) { // Collide on Right of Character
            newPos.x = posOb.x-sizeCh.x-deltaPosCharaCollider.x -offcet;
            newSpeed.x = 0;

        } else if (UD > LR && UD > DU) { // Collide on Up of Character
            newPos.y = posOb.y+sizeOb.y-deltaPosCharaCollider.y +offcet;
            newSpeed.y = 0;

        } else if (LR > DU) { // Collide on Left of Character
            newPos.x = posOb.x+sizeOb.x-deltaPosCharaCollider.x +offcet;
            newSpeed.x = 0;

        } else { // Collide on Down of Character
            newPos.y = posOb.y-sizeCh.y-deltaPosCharaCollider.y -offcet;
            newSpeed.y = 0;

        }
        setPosition(newPos);
        setSpeed(newSpeed);


    } else {
        Equipment * equipement = dynamic_cast<Equipment*>(weColided);
        if (equipement) {
            setEquipment(equipement);
        }
    }
}

void BaseCharacter::setDown(bool down)
{
    _down = down;
    updateAnimatonId(_down, _up, _left, _right, WALK_FRONT, STAY_STILL_FRONT,
                     WALK_BACK, STAY_STILL_BACK, WALK_LEFT, WALK_RIGHT);

}
void BaseCharacter::setLeft(bool left)
{
    _left = left;
    updateAnimatonId(_left, _right, _up, _down, WALK_LEFT, STAY_STILL_LEFT,
                     WALK_RIGHT, STAY_STILL_RIGHT, WALK_BACK, WALK_FRONT);
}
void BaseCharacter::setRight(bool right)
{
    _right = right;
    updateAnimatonId(_right, _left, _down, _up, WALK_RIGHT, STAY_STILL_RIGHT,
                     WALK_LEFT, STAY_STILL_LEFT, WALK_FRONT, WALK_BACK);
}
void BaseCharacter::setUp(bool up)
{
    _up = up;
    updateAnimatonId(_up, _down, _right, _left, WALK_BACK, STAY_STILL_BACK,
                     WALK_FRONT, STAY_STILL_FRONT, WALK_RIGHT, WALK_LEFT);
}

// south is the direction which changed
void BaseCharacter::updateAnimatonId(bool south, bool north, bool weast, bool east,
                      int southWalk, int southStay, int northWalk, int northStay, int weastWalk, int eastWalk)
{
    if (south) {
        if (weast==east and !north) {
            setAnimation(southWalk);
        } else if (weast==east and north) {
            setAnimation(northStay);
        } else if (weast and north) {
            setAnimation(weastWalk);
        } else if (east and north) {
            setAnimation(eastWalk);
        }
    } else {
        if (weast==east and !north) {
            setAnimation(southStay);
        } else if (weast==east and north) {
            setAnimation(northWalk);
        } else if (weast and !north) {
            setAnimation(weastWalk);
        } else if (east and !north) {
            setAnimation(eastWalk);
        }
    }
}

void BaseCharacter::setAnimation(int animationId)
{
    AnimatedSprite::setAnimation(animationId);
    for (auto pair:_equipments) {
        pair.second->setAnimation(animationId);
    }
}

void BaseCharacter::setEquipment(Equipment *equipment)
{
    auto it = _equipments.find(equipment->getType());
    if (it != _equipments.end()) {

        it->second->setParent(Moteur2D::getInstance()->getCurrentScreen(), 10);
        it->second->setPosition(getPosition() + getSpeed().normalize()*getAbsoluteSize().x*-1.5);
        it->second->getCollider()->setCollisionEnabled(true);
        it->second->setAnimation(STAY_STILL_FRONT);
    }
    _equipments[equipment->getType()] = equipment;
    equipment->setParent(this, equipment->getType());
    equipment->setPosition(Vector2d(0, 0));
    equipment->getCollider()->setCollisionEnabled(false);
    setAnimation(getAnimationId());

}

