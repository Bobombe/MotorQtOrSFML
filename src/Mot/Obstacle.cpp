#include "Obstacle.h"

Obstacle::Obstacle(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, WorldElement * parent) :
    Sprite(texturePath, subRectPos, subRectSize)
{
    setParent(parent);

    // Add in first screen parent
    Screen * screen = dynamic_cast<Screen*>(parent);
    while (!screen && parent) {
        parent = parent->getParent();
        screen = dynamic_cast<Screen*>(parent);
    }
    if (screen) {
        _collider =  new Collider(this);
        _collider->initRectangular(0, 0, getSize().x, getSize().y);
        screen->addCollider(0, _collider);
    } else {
        std::cout << "[ERROR] Obstacle created out of a Screen." << std::endl;
    }
}
Obstacle::Obstacle(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, Vector2d spriteSize, WorldElement * parent) :
    Sprite(texturePath, subRectPos, subRectSize, spriteSize)
{
    setParent(parent);

    // Add in first screen parent
    Screen * screen = dynamic_cast<Screen*>(parent);
    while (!screen && parent) {
        parent = parent->getParent();
        screen = dynamic_cast<Screen*>(parent);
    }
    if (screen) {
        _collider =  new Collider(this);
        _collider->initRectangular(0, 0, getSize().x, getSize().y);
        screen->addCollider(0, _collider);
    } else {
        std::cout << "[ERROR] Obstacle created out of a Screen." << std::endl;
    }
}

Obstacle::~Obstacle()
{
    if (_collider) {
        WorldElement * parent = getParent();
        Screen * screen = dynamic_cast<Screen*>(parent);
        while (!screen && parent) {
            parent = parent->getParent();
            screen = dynamic_cast<Screen*>(parent);
        }
        if (screen) {
            screen->deleteCollider(0, _collider);
        }
    }
}
