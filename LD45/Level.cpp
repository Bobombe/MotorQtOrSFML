#include "Level.h"
#include "moteur2d.h"
#include "Sound.h"
#include "Equipment.h"
#include <fstream>

Level::Level():
    Screen()
{
    addEquipement(Equipment::PANTS, "Ressources/GreenPants.png", 100, 100);
    addEquipement(Equipment::SHOES, "Ressources/RedShoes.png", 150, 200);
    addEquipement(Equipment::SHOES, "Ressources/GreenShoes.png", 350, 200);
    addEquipement(Equipment::WEAPON, "Ressources/Stick.png", 400, 100);
    addEquipement(Equipment::SHIRT, "Ressources/GreenShirt.png", 100, 170);
    addEquipement(Equipment::WEAPON, "Ressources/Sword.png", 500, 600);
    addEquipement(Equipment::CAP, "Ressources/Helmet.png", 896, 530, 0);
}

Level::~Level()
{
}

int Level::draw()
{
    int retValue = 0;
    /*Vector2d pos(_player->getPosition());
    if (pos.x > 120 && pos.x < 150 && pos.y > 170 && pos.y < 200) {
        _player->setEquipment(_equipement);
    }//*/

    Screen::draw();
    return retValue;
}

void Level::setPlayer(Player * player)
{
    _player = player;
    _player->setParent(this, 10);
    _player->setScreenIdKeyboard(getScreenId());
    addCollider(0, _player->getCollider());
}

void Level::readLevel(std::string lvlFilePath)
{
    Vector2d tileSize{32, 32};
    if (_currentLevel) {
        delete _currentLevel;
    }
    _currentLevel = new WorldElement(this, 1);

    // Read file in lvlRepresentation
    std::vector<std::string> lvlRepresentation;
    std::ifstream lvl(lvlFilePath);
    std::string line;
    if (lvl.is_open()) {
        bool onObstacle{false};
      while ( !onObstacle && getline (lvl,line) ) {
          if (line == "# Obstacle") {
              onObstacle = true;
          }
      }
      // Reading tiles and obstacles
      while ( onObstacle && getline (lvl,line) ) {
          if (line == "# END Obstacle") {
              onObstacle = false;
          } else {
              lvlRepresentation.push_back(line);
          }
      }
      lvl.close();
    }

    // Creating corresponding sprites
    for (unsigned int j = 0; j < lvlRepresentation.size(); j++) {
        std::string &line = lvlRepresentation[j];
        for (unsigned int i = 0; i < line.size(); i++) {
            Vector2d pos(i*tileSize.x, j*tileSize.y);

            switch(line[i]) {
            case 'h': {
                addHerbe(i, j, lvlRepresentation, pos);
                break;
            }

            case 'c': {
                Sprite* c = new Sprite("Ressources/Chemin.png");
                c->setPosition(pos);
                c->setParent(_currentLevel);
                break;
            }

            case 't': {
                addHerbe(i, j, lvlRepresentation, pos);
                Sprite* t = new Sprite("Ressources/Tree.png");
                t->setPosition(pos);
                t->setParent(_currentLevel, 1);
                t->setCollider(new Collider(t));
                t->getCollider()->initRectangular(3, 35, 26, 26);
                t->setWeName("Obstacle");
                addCollider(0, t->getCollider());
                lvlRepresentation[j+1][i] = 'h';
                break;
            }

            case 'm': {
                addHerbe(i, j, lvlRepresentation, pos);
                Sprite* t = new Sprite("Ressources/House.png");
                t->setPosition(pos);
                t->setParent(_currentLevel, 1);
                t->setCollider(new Collider(t));
                t->getCollider()->initRectangular(6, 45, 85, 44);
                t->setWeName("Obstacle");
                addCollider(0, t->getCollider());
                lvlRepresentation[j][i+1] = 'h';
                lvlRepresentation[j][i+2] = 'h';
                lvlRepresentation[j+1][i] = 'h';
                lvlRepresentation[j+1][i+1] = 'h';
                lvlRepresentation[j+1][i+2] = 'h';
                lvlRepresentation[j+2][i] = 'h';
                lvlRepresentation[j+2][i+1] = 'h';
                lvlRepresentation[j+2][i+2] = 'h';
                break;
            }
            case 'p': {
                _player->setPosition(pos);
                Sprite* c = new Sprite("Ressources/Chemin.png");
                c->setPosition(pos);
                c->setParent(_currentLevel);
                break;
            }



            }
        }
    }

}
void Level::addHerbe(unsigned int i, unsigned int j, const std::vector<std::string> &lvlRepresentation, const Vector2d &pos)
{
    const std::string & line = lvlRepresentation[j];
    Sprite* h = new Sprite("Ressources/Herbe.png");
    h->setPosition(pos);
    h->setParent(_currentLevel);

    // Looking for dirtPath
    bool dirtFound = false;
    if (j > 0) { // North
        if (lvlRepresentation[j-1][i] == 'c' or lvlRepresentation[j-1][i] == 'p') {
            Sprite* c = new Sprite("Ressources/CheminSud.png");
            c->setPosition(pos);
            c->setParent(_currentLevel);
            dirtFound = true;
        }
    }
    if (i < line.size()-1) { // East
        if (lvlRepresentation[j][i+1] == 'c' or lvlRepresentation[j][i+1] == 'p') {
            Sprite* c = new Sprite("Ressources/CheminOuest.png");
            c->setPosition(pos);
            c->setParent(_currentLevel);
            dirtFound = true;
        }
    }
    if (j < lvlRepresentation.size()-1) { // South
        if (lvlRepresentation[j+1][i] == 'c' or lvlRepresentation[j+1][i] == 'p') {
            Sprite* c = new Sprite("Ressources/CheminNord.png");
            c->setPosition(pos);
            c->setParent(_currentLevel);
            dirtFound = true;
        }
    }
    if (i > 0) { // West
        if (lvlRepresentation[j][i-1] == 'c' or lvlRepresentation[j][i-1] == 'p') {
            Sprite* c = new Sprite("Ressources/CheminEst.png");
            c->setPosition(pos);
            c->setParent(_currentLevel);
            dirtFound = true;
        }
    }
    if (!dirtFound) {
        if (j > 0 && i < line.size()-1) { // North East
            if (lvlRepresentation[j-1][i+1] == 'c' or lvlRepresentation[j-1][i+1] == 'p') {
                Sprite* c = new Sprite("Ressources/CheminSudOuest.png");
                c->setPosition(pos);
                c->setParent(_currentLevel);
                dirtFound = true;
            }
        }
        if (j > 0 && i > 0) { // North West
            if (lvlRepresentation[j-1][i-1] == 'c' or lvlRepresentation[j-1][i-1] == 'p') {
                Sprite* c = new Sprite("Ressources/CheminSudEst.png");
                c->setPosition(pos);
                c->setParent(_currentLevel);
                dirtFound = true;
            }
        }
        if (j < lvlRepresentation.size()-1 && i < line.size()-1) { // South Eest
            if (lvlRepresentation[j+1][i+1] == 'c' or lvlRepresentation[j+1][i+1] == 'p') {
                Sprite* c = new Sprite("Ressources/CheminNordOuest.png");
                c->setPosition(pos);
                c->setParent(_currentLevel);
                dirtFound = true;
            }
        }
        if (j < lvlRepresentation.size()-1 && i > 0) { // South West
            if (lvlRepresentation[j+1][i-1] == 'c' or lvlRepresentation[j+1][i-1] == 'p') {
                Sprite* c = new Sprite("Ressources/CheminNordEst.png");
                c->setPosition(pos);
                c->setParent(_currentLevel);
                dirtFound = true;
            }
        }
    }

}

void Level::addEquipement(Equipment::EquipmentType type, std::string texturePath, double posX, double posY, int level)
{
    Equipment* equipement = new Equipment(texturePath);
    equipement->setType(type);
    equipement->setParent(this, level);
    equipement->setPosition(Vector2d(posX, posY));
    addCollider(0, equipement->getCollider());
}
