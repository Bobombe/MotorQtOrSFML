
#include "ScreenManagerLD45.h"
#include "LD45/TitleScreen.h"
#include "Level.h"

ScreenManagerLD45::ScreenManagerLD45():
    _stateMachine(0)
{
    addScreen(0, new ld45::TitleScreen());
    setCurrentScreenId(0);
}

ScreenManagerLD45::~ScreenManagerLD45()
{
}

void ScreenManagerLD45::update(double, int, int drawReturn)
{
    if (getCurrentScreenId() == 0 && drawReturn == 1) {
        deleteScreen(0);
        Level* l = new Level;
        addScreen(1, l);
        setCurrentScreenId(1);
        l->setPlayer(&_player);
        _player.setEquipment(new Equipment("Ressources/Censure.png"));
        l->readLevel("Ressources/Level1.lvl");
    }
}
