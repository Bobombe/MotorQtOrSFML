

#include "Texture.h"

Texture::Texture(std::string pathToTexture) : _useNumber(0), _texturePath(pathToTexture)
{

#ifdef IN_QT

#else
    _texture = new sf::Texture();
    if(!_texture->loadFromFile(imagePath))
    {
        // problem !
        delete _texture;
        _texture = 0;
        std::cout << "ERROR : Texture::Texture can't load " << imagePath << std::endl;
        return 0;
    }
#endif
}

Texture::~Texture()
{

#ifdef IN_QT

#else
    delete _texture;
#endif
}


#ifdef IN_QT
// Todo : might need a qt dependent return class
Texture*
#else
sf::Texture*
#endif
Texture::getTexture()
{
    _useNumber++;
#ifdef IN_QT
    // Todo
    return this;
#else
    if (!_texture) {
        _useNumber--;
    }
    return _texture
#endif
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
