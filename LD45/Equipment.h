#ifndef Equipment_H
#define Equipment_H

#include "BaseAnimatedSprite.h"

class Equipment : public BaseAnimatedSprite
{
public:

    enum EquipmentType {
        NONE = 0,
        SHOES,
        PANTS,
        SHIRT,
        VEST,
        FACIAL_HAIR,
        GLASSES,
        CAP,
        WEAPON
    };

    Equipment(std::string equipedTexturePath/*, std::string onGroundTexturePath*/);

    //int draw() override;
    EquipmentType getType();
    void setType(EquipmentType type);

protected:

private:
    EquipmentType _type{NONE};
    bool _onGround{true};
    bool _equiped{false};
    Sprite _spriteOnGround;



};

#endif // Equipment_H
