

#include "Texture.h"
#include <iostream>
#include <string>

Texture::Texture(std::string pathToTexture) : _useNumber(0), _texturePath(pathToTexture)
{

#ifdef IN_QT
    _texture = new QPixmap();
    QString path(pathToTexture.c_str());
    if(!_texture->load(path))
    {
        // problem !
        delete _texture;
        _texture = 0;
        std::cout << "ERROR : Texture::Texture can't load " << pathToTexture << std::endl;
    }
    else
    {
        _size.x = _texture->size().width();
        _size.y = _texture->size().height();
    }

#else

    _texture = new sf::Texture();
    if(!_texture->loadFromFile(pathToTexture))
    {
        // problem !
        delete _texture;
        _texture = 0;
        std::cout << "ERROR : Texture::Texture can't load " << pathToTexture << std::endl;
    }
    else
    {
        _size.x = _texture->getSize().x;
        _size.y = _texture->getSize().y;
    }
    _texture->setSmooth(true);
#endif
}

Texture::~Texture()
{

    delete _texture;
}


CoreTexture * Texture::getTexture()
{
    _useNumber++;
    if (!_texture) {
        _useNumber--;
    }
    return _texture;
}

bool Texture::freeTexture()
{
    _useNumber--;
    if (_useNumber == 0)
    {
        return true;
    }
    return false;
}

Vector2d Texture::getSize()
{
    return _size;
}


