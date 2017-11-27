
#include "Sprite.h"
#include "moteur2d.h"


#ifdef IN_QT
#include <QRect>
#include <QPainter>
#else
#include <SFML/Graphics.hpp>
#endif

Sprite::Sprite()
{
    _texture = 0;
#ifdef IN_QT
    _manipulationItem = 0;
#else
    _intermediateTexture = 0;
#endif
}
Sprite::Sprite(std::string texturePath)
{
#ifdef IN_QT
    _manipulationItem = 0;
#else
    _intermediateTexture = 0;
#endif
    setSprite(texturePath, Vector2d(), Vector2d());
}
Sprite::Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize)
{
#ifdef IN_QT
    _manipulationItem = 0;
#else
    _intermediateTexture = 0;
#endif
    setSprite(texturePath, subRectPos, subRectSize);
}
Sprite::Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, Vector2d spriteSize)
{
#ifdef IN_QT
    _manipulationItem = 0;
#else
    _intermediateTexture = 0;
#endif
    setSprite(texturePath, subRectPos, subRectSize, spriteSize);
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
    if (_intermediateTexture) {
        delete _intermediateTexture;
    }

#endif
}


int Sprite::draw(Vector2d pos, float scale)
{
#ifdef IN_QT
    _manipulationItem->setPos(_pos.x*scale + pos.x, _pos.y*scale + pos.y);
    _manipulationItem->setScale(_scale*scale);

#else

    _sprite.setPosition(_pos.x*scale + pos.x, _pos.y*scale + pos.y);
    _sprite.scale(_scale*scale, _scale*scale);
    Moteur2D::getInstance()->getWindow()->draw(_sprite);
#endif
    return WorldElement::draw(pos, scale);
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
    _size = _subRectSize;

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
void Sprite::setSprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, Vector2d spriteSize)
{
    _subRectPos = subRectPos;
    _subRectSize = subRectSize;
    _size = spriteSize;
    // if null size, take the whole texture as sprite
    if (_subRectSize.x == 0 && _subRectSize.y == 0)
    {
        _subRectSize = _texture->getSize();
        _subRectPos.x = _subRectPos.y = 0;
    }
    if (subRectSize == spriteSize) {
        setSprite(texturePath, _subRectPos, _subRectSize);
    } else {

        if (_texturePath != texturePath)
        {
            Moteur2D::getInstance()->unloadTexture(_texturePath);
            _texturePath = texturePath;
            _texture = Moteur2D::getInstance()->getTexture(_texturePath);
        }


    #ifdef IN_QT
        _sprite = CoreSprite(_size.x, _size.y);
        _sprite.fill(Qt::transparent);
        CoreSprite* texture = _texture->getTexture();
        QPainter painter(&_sprite);
        for (double i = 0; i < _size.x; i+=_subRectSize.x) {
            for (double j = 0; j < _size.y; j+=_subRectSize.y) {
                painter.drawPixmap(i, j, _subRectSize.x, _subRectSize.y, *texture
                        , _subRectPos.x, _subRectPos.y, _subRectSize.x, _subRectSize.y);
            }

        }
        painter.end();
        if (_manipulationItem)
        {
            _manipulationItem->setPixmap(_sprite);
        }

    #else
        sf::Image smallImg;
        sf::Image imgFromTexture;
        smallImg.create(_subRectSize.x, _subRectSize.y);
        imgFromTexture.loadFromFile(texturePath);
        for (int i = 0; i < _subRectSize.x; ++i) {
            for (int j = 0; j<_subRectSize.y; ++j) {
                smallImg.setPixel(i, j, imgFromTexture.getPixel(_subRectPos.x + i, _subRectPos.y + j));
            }
        }

        if (_intermediateTexture) {
            delete _intermediateTexture;
        }
        _intermediateTexture = new sf::Texture();
        _intermediateTexture->loadFromImage(smallImg);
        _intermediateTexture->setRepeated(true);
        _sprite.setTexture(*_intermediateTexture);
        sf::IntRect subTextureRect(0, 0, _size.x, _size.y);
        _sprite.setTextureRect(subTextureRect);

    #endif
    }
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

Vector2d Sprite::getSize()
{
    return _size;
}
void Sprite::setSize(Vector2d spriteSize)
{
    setSprite(_texturePath, _subRectPos, _subRectSize, spriteSize);
}

void Sprite::setSubRect(Vector2d subRectPos, Vector2d subRectSize)
{
    setSprite(_texturePath, subRectPos, subRectSize);
}

void Sprite::setScale(float scale)
{
    if (scale != _scale) {
        _scale = scale;
    }
}


// Specifics Functions
#ifdef IN_QT
void Sprite::addedInScene(QGraphicsScene * scene)
{
    _manipulationItem = scene->addPixmap(_sprite);
    _manipulationItem->setScale(_scale);
}

#else

#endif
