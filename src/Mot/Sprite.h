
#ifndef SRC_MOT_SPRITE_H_
#define SRC_MOT_SPRITE_H_

#include "Texture.h"
#include "WorldElement.h"

#ifdef IN_QT
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#define CoreSprite QPixmap

#else

#define CoreSprite sf::Sprite
#endif

class Sprite : public WorldElement
{

protected:

    CoreSprite _sprite;
    std::string _texturePath;
    Texture * _texture;

    Vector2d _subRectPos;
    Vector2d _subRectSize;
    Vector2d _spriteSize;

#ifdef IN_QT
    QGraphicsPixmapItem* _manipulationItem;

#else

#endif

public:
    Sprite();
    Sprite(std::string texturePath);
    Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize);
    Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, Vector2d spriteSize);
    virtual ~Sprite();

    CoreSprite getCoreSprite();

    // Getters and Setters
    void setSprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize);
    void setSprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, Vector2d spriteSize);

    std::string getTexturePath();
    void setTexturePath(std::string texturePath);

    Vector2d getSubRectPos();
    void setSubRectPos(Vector2d subRectPos);

    Vector2d getSubRectSize();
    void setSubRectSize(Vector2d subRectSize);

    Vector2d getSize();
    void setSize(Vector2d spriteSize);

    void setSubRect(Vector2d subRectPos, Vector2d subRectSize);


    // Specifics Functions
#ifdef IN_QT
    virtual void addedInScene(QGraphicsScene * scene);

#else

#endif

protected:

    virtual int draw(Vector2d pos = Vector2d());
};

#endif /* SRC_MOT_SPRITE_H_ */
