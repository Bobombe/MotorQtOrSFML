#ifndef Level_H
#define Level_H

#include "Button.h"
#include "Screen.h"
#include "Sound.h"
#include "Player.h"

class Level: public Screen
{
protected:

public:
    Level();
    virtual ~Level();

    void setPlayer(Player * player);
    void readLevel(std::string lvlFilePath);

protected:
    virtual int draw();

    void addHerbe(unsigned int i, unsigned int j, const std::vector<std::string> &lvlRepresentation, const Vector2d &pos);

    void addEquipement(Equipment::EquipmentType type, std::string texturePath, double posX, double posY, int level = 10);

private:
    Player * _player{nullptr};
    WorldElement * _currentLevel{nullptr};
};

#endif // Level_H
