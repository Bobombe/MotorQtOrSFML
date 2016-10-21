
#include "Sprite.h"
#include "moteur2d.h"


#ifdef IN_QT
#include <QRect>
#else

#endif

Sprite::Sprite()
{
    _texture = 0;
#ifdef IN_QT
    _manipulationItem = 0;
#else

#endif
}
Sprite::Sprite(std::string texturePath)
{
    setSprite(texturePath, Vector2d(), Vector2d());
}
Sprite::Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize)
{
    setSprite(texturePath, subRectPos, subRectSize);
}

Sprite::~Sprite()
{
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

    _sprite.setPosition(_pos+pos);
    Moteur2D::getInstance()->getWindow()->draw(_sprite);
#endif
    return 0;
}

CoreSprite Sprite::getCoreSprite()
{
    return _sprite;
}


// Getters and Setters

void Sprite::setSprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize)
{
    if (_texturePath != texturePath)
    {
        Moteur2D::getInstance()->unloadTexture(_texturePath);
        _texturePath = texturePath;
        _texture = Moteur2D::getInstance()->getTexture(_texturePath);
    }

    _subRectPos = subRectPos;
    _subRectSize = subRectSize;
    // if null size, take the whole texture as sprite
    if (_subRectSize.x == 0 && _subRectSize.y == 0)
    {
        _subRectSize = _texture->getSize();
        _subRectPos.x = _subRectPos.y = 0;
    }

#ifdef IN_QT
    _sprite = _texture->getTexture()->copy(_subRectPos.x, _subRectPos.y, _subRectSize.x, _subRectSize.y);
    if (_manipulationItem)
    {
        _manipulationItem->setPixmap(_sprite);
    }

#else
    _sprite.setTexture(*(_texture->getTexture()));
    sf::IntRect subTextureRect(_subRectPos.x, _subRectPos.y, _subRectSize.x, _subRectSize.y);
    _sprite.setTextureRect(subTextureRect);

#endif
}

std::string Sprite::getTexturePath()
{
    return _texturePath;
}
void Sprite::setTexturePath(std::string texturePath)
{
    setSprite(texturePath, _subRectPos, _subRectSize);
}

Vector2d Sprite::getSubRectPos()
{
    return _subRectPos;
}
void Sprite::setSubRectPos(Vector2d subRectPos)
{
    setSprite(_texturePath, subRectPos, _subRectSize);
}

Vector2d Sprite::getSubRectSize()
{
    return _subRectSize;
}
void Sprite::setSubRectSize(Vector2d subRectSize)
{
    setSprite(_texturePath, _subRectPos, subRectSize);
}

void Sprite::setSubRect(Vector2d subRectPos, Vector2d subRectSize)
{
    setSprite(_texturePath, subRectPos, subRectSize);
}


// Specifics Functions
#ifdef IN_QT
void Sprite::addedInScene(QGraphicsScene * scene)
{
    _manipulationItem = scene->addPixmap(_sprite);
    _manipulationItem->setPos(_pos.x, _pos.y);
}

#else

#endif
