
#ifndef SRC_MOT_TEXTURE_H_
#define SRC_MOT_TEXTURE_H_

#include <string>

#ifdef IN_QT

#else
#include <SFML/Graphics.hpp>
#endif

class Texture {

protected:
    int _useNumber;
    std::string _texturePath;

#ifdef IN_QT

#else
    sf::Texture * _texture;
#endif

public:
    Texture(std::string pathToTexture);
    virtual ~Texture();

    // Return null if texture is invalid => Texture must be deleted
#ifdef IN_QT
        // Todo : might need a qt dependent return class
        Texture*
#else
        sf::Texture*
#endif
    getTexture();

    // return true if texture not used anymore, might need to be deleted.
    bool freeTexture();
};

#endif
