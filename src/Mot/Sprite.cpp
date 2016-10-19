
#include "Sprite.h"
#include "moteur2d.h"


#ifdef IN_QT
#include <QRect>
#else

#endif

Sprite::Sprite()
{
    _sprite = 0;
    _texture = 0;
#ifdef IN_QT
    _manipulationItem = 0;
#else

#endif
}
Sprite::Sprite(std::string texturePath) : _texturePath(texturePath)
{
    _texture = Moteur2D::getInstance()->getTexture(texturePath);
#ifdef IN_QT
    _sprite = new QPixmap(_texture->getTexture()->copy(QRect()));
    _manipulationItem = 0;
#else

#endif
}
Sprite::Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize) : _texturePath(texturePath)
{

    _texture = Moteur2D::getInstance()->getTexture(texturePath);
#ifdef IN_QT
    _sprite = new QPixmap(_texture->getTexture()->copy(subRectPos.x, subRectPos.y, subRectSize.x, subRectSize.y));
    _manipulationItem = 0;
#else

#endif
}

Sprite::~Sprite()
{
    if (_sprite)
    {
        delete _sprite;
    }
    Moteur2D::getInstance()->unloadTexture(_texturePath);
#ifdef IN_QT
    if (_manipulationItem)
    {
        delete _manipulationItem;
    }

#else

#endif
}


int Sprite::draw(Vector2d pos)
{
#ifdef IN_QT
    _manipulationItem->setPos(_pos.x + pos.x, _pos.y + pos.y);

#else

#endif
    return 0;
}

CoreSprite* Sprite::getCoreSprite()
{
    return _sprite;
}


// Getters and Setters
Vector2d Sprite::getSubRectPos()
{
    return _subRectPos;
}
void Sprite::setSubRectPos(Vector2d subRectPos)
{
    _subRectPos = subRectPos;
    *_sprite = _texture->getTexture()->copy(_subRectPos.x, _subRectPos.y, _subRectSize.x, _subRectSize.y);
    _manipulationItem->setPixmap(*_sprite);
}

Vector2d Sprite::getSubRectSize()
{
    return _subRectSize;
}
void Sprite::setSubRectSize(Vector2d subRectSize)
{
    _subRectSize = subRectSize;
    *_sprite = _texture->getTexture()->copy(_subRectPos.x, _subRectPos.y, _subRectSize.x, _subRectSize.y);
    _manipulationItem->setPixmap(*_sprite);
}

void Sprite::setSubRect(Vector2d subRectPos, Vector2d subRectSize)
{
    _subRectPos = subRectPos;
    _subRectSize = subRectSize;
    *_sprite = _texture->getTexture()->copy(_subRectPos.x, _subRectPos.y, _subRectSize.x, _subRectSize.y);
    _manipulationItem->setPixmap(*_sprite);
}


// Specifics Functions
#ifdef IN_QT
void Sprite::addedInScene(QGraphicsScene * scene)
{
    _manipulationItem = scene->addPixmap(*_sprite);
    _manipulationItem->setPos(_pos.x, _pos.y);
}

#else

#endif
