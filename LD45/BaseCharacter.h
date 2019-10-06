#ifndef BASECHARACTER_H
#define BASECHARACTER_H

#include "BaseAnimatedSprite.h"
#include "Equipment.h"

class BaseCharacter : public BaseAnimatedSprite
{
public:

    BaseCharacter();

    int update(double seconds) override;
    void handleCollisionWith(WorldElement * weColided, double secsSinceLastFrame, int nbAdditionnalInfo...) override;

    void setDown(bool down);
    void setLeft(bool left);
    void setRight(bool right);
    void setUp(bool up);

    void setAnimation(int animationId);

    void setEquipment(Equipment *equipment);

protected:
    void updateAnimatonId(bool south, bool north, bool weast, bool east,
                          int southWalk, int southStay, int northWalk, int northStay, int weastWalk, int eastWalk);

private:
    bool _down{false};
    bool _left{false};
    bool _right{false};
    bool _up{false};

    std::map<Equipment::EquipmentType, Equipment*> _equipments;


};

#endif // BASECHARACTER_H
