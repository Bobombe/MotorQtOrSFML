
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

class Sprite: public WorldElement
{
private:
    static int _s_layer;

protected:
    CoreSprite  _sprite;
    std::string _texturePath;
    Texture     *_texture;

    Vector2d _subRectPos;
    Vector2d _subRectSize;

#ifdef IN_QT
    QGraphicsPixmapItem *_manipulationItem;

#else
    sf::Texture *_intermediateTexture;
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
    void        setTexturePath(std::string texturePath);

    Vector2d getSubRectPos();
    void     setSubRectPos(Vector2d subRectPos);

    Vector2d getSubRectSize();
    void     setSubRectSize(Vector2d subRectSize);

    void setSubRect(Vector2d subRectPos, Vector2d subRectSize);

protected:
    virtual int update(double seconds);
    virtual int draw();

    // Specifics Functions
#ifdef IN_QT
    virtual void updateScene(QGraphicsScene *scene);

#else

#endif
};

#endif /* SRC_MOT_SPRITE_H_ */
