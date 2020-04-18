#ifndef TEXT_H
#define TEXT_H

#include "WorldElement.h"

#ifdef IN_QT
#include <QGraphicsTextItem>
#else
#include <SFML/Graphics.hpp>
#endif

class Text : public WorldElement
{
protected:
#ifdef IN_QT
    QGraphicsTextItem *_coreText;
    QFont _font;
#else
    sf::Text _coreText;
#endif

    std::string _text;

public:

    enum Style {
        Regular = 0,
        Bold = 1 << 0,
        Italic = 1 << 1,
        Underlined = 1 << 2,
        StrikeThrough = 1 << 3
    };
    enum Color {
        Black,
        White,
        Red,
        Green,
        Blue,
        Yellow,
        Magenta,
        Cyan
    };

    Text();
    Text(WorldElement * parent, int layer = 0);
    Text(std::string text, WorldElement * parent=0, int layer = 0);
    virtual ~Text();
    void init(std::string text);

    void setText(std::string text);
    std::string getText();

    void setCharacterSize(unsigned int size);
    void setStyle(unsigned int style);
    void setColor(Color color);

protected:

    virtual int draw();
    void updateSize();

    // Specifics Functions
    #ifdef IN_QT
    virtual void updateScene(QGraphicsScene * scene);

    #else

    #endif
};

#endif // TEXT_H
