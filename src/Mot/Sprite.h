
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

    CoreSprite * _sprite;
    std::string _texturePath;
    Texture * _texture;

    Vector2d _subRectPos;
    Vector2d _subRectSize;

#ifdef IN_QT
    QGraphicsPixmapItem* _manipulationItem;

#else

#endif

public:
    Sprite();
    Sprite(std::string texturePath);
    Sprite(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize);
    virtual ~Sprite();

    virtual int draw(Vector2d pos = Vector2d());

    CoreSprite* getCoreSprite();

    // Getters and Setters
    Vector2d getSubRectPos();
    void setSubRectPos(Vector2d subRectPos);

    Vector2d getSubRectSize();
    void setSubRectSize(Vector2d subRectSize);

    void setSubRect(Vector2d subRectPos, Vector2d subRectSize);


    // Specifics Functions
#ifdef IN_QT
    virtual void addedInScene(QGraphicsScene * scene);

#else

#endif
};

#endif /* SRC_MOT_SPRITE_H_ */
