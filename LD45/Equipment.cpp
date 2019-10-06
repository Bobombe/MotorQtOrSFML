#include "Equipment.h"

Equipment::Equipment(std::string equipedTexturePath/*, std::string onGroundTexturePath*/) :
    BaseAnimatedSprite(equipedTexturePath)/*, _spriteOnGround(onGroundTexturePath)*/
{

}
/*
int Equipment::draw()
{
    int ret = 0;
    if (_onGround) {
        ret = _spriteOnGround.baseDraw();
    } else if (_equiped) {
        ret = BaseAnimatedSprite::draw();
    }
    return ret;
}
*/
Equipment::EquipmentType Equipment::getType()
{
    return _type;
}

void Equipment::setType(EquipmentType type)
{
    _type = type;
}
