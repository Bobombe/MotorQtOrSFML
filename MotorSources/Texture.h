
#ifndef SRC_MOT_TEXTURE_H_
#define SRC_MOT_TEXTURE_H_

#include <string>
#include "Vector2d.h"

#ifdef IN_QT
#define CoreTexture QPixmap
#include <QPixmap>
#else
#define CoreTexture sf::Texture
#include <SFML/Graphics.hpp>
#endif

class Texture {

protected:
    int _useNumber;
    std::string _texturePath;

    CoreTexture * _texture;

    Vector2d _size;

public:
    Texture(std::string pathToTexture);
    virtual ~Texture();

    // Return null if texture is invalid => Texture must be deleted
    CoreTexture * getTexture();

    // return true if texture not used anymore, might need to be deleted.
    bool freeTexture();

    Vector2d getSize();
};

#endif
