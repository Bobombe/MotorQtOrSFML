#include "Text.h"
#include "moteur2d.h"

Text::Text() : WorldElement()
{
    init("");
}
Text::Text(WorldElement * parent) : WorldElement(parent)
{
    init("");
}
Text::Text(std::string text, WorldElement * parent) : WorldElement(parent)
{
    init(text);
}

Text::~Text()
{
}

void Text::init(std::string text)
{
    _collider = new Collider(this);
#ifdef IN_QT

#else
    _coreText.setFont(Moteur2D::getInstance()->getFont());
    _coreText.setCharacterSize(30);
    _coreText.setStyle(sf::Text::Italic);
    _coreText.setColor(sf::Color::Black);
#endif
    setText(text);
}

void Text::setText(std::string text)
{
    _text = text;
#ifdef IN_QT

#else
    _coreText.setString(text);
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}
std::string Text::getText()
{
    return _text;
}

void Text::setCharacterSize(unsigned int size)
{

#ifdef IN_QT

#else
    _coreText.setCharacterSize(size);
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}
void Text::setStyle(unsigned int style)
{

#ifdef IN_QT

#else
    _coreText.setStyle(style);
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}

void Text::setColor(Color color)
{
#ifdef IN_QT

#else
    switch (color) {
    case Black:
        _coreText.setColor(sf::Color::Black);
        break;
    case White:
        _coreText.setColor(sf::Color::White);
        break;
    case Red:
        _coreText.setColor(sf::Color::Red);
        break;
    case Green:
        _coreText.setColor(sf::Color::Green);
        break;
    case Blue:
        _coreText.setColor(sf::Color::Blue);
        break;
    case Yellow:
        _coreText.setColor(sf::Color::Yellow);
        break;
    case Magenta:
        _coreText.setColor(sf::Color::Magenta);
        break;
    case Cyan:
        _coreText.setColor(sf::Color::Cyan);
        break;
    }
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}


int Text::draw()
{
#ifdef IN_QT

#else

    _coreText.setPosition(getAbsolutePosition().x, getAbsolutePosition().y);
    _coreText.setScale(getAbsoluteScale(), getAbsoluteScale());
    Moteur2D::getInstance()->getWindow()->draw(_coreText);
#endif
    int ret = WorldElement::draw();
    return ret;
}
