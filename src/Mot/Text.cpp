#include "Text.h"
#include "moteur2d.h"

#ifdef IN_QT
#include <QFontDatabase>
#else
#endif

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
    _weName = "Text";
    _collider = new Collider(this);
#ifdef IN_QT

    int id = QFontDatabase::addApplicationFont("./motorResources/OpenSans-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);


    _coreText = new QGraphicsTextItem();
    _coreText->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
    _font.setFamily(family);
    _font.setPixelSize(30);
    _coreText->setFont(_font);
#else
    _coreText.setFont(Moteur2D::getInstance()->getFont());
    _coreText.setCharacterSize(30);
    _coreText.setColor(sf::Color::Black);
#endif
    setText(text);
    setParent(_parent);
}

void Text::setText(std::string text)
{
    _text = text;
#ifdef IN_QT
    _coreText->setPlainText(QString::fromStdString(text));
    setSize(Vector2d(_coreText->boundingRect().width(), _coreText->boundingRect().height()));
    _collider->initRectangular(0, 0, _coreText->boundingRect().width(), _coreText->boundingRect().height());
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

    _font.setPixelSize(size);
    _coreText->setFont(_font);
    setSize(Vector2d(_coreText->boundingRect().width(), _coreText->boundingRect().height()));
    _collider->initRectangular(0, 0, _coreText->boundingRect().width(), _coreText->boundingRect().height());
#else
    _coreText.setCharacterSize(size);
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}
void Text::setStyle(unsigned int style)
{

#ifdef IN_QT
    _font.setBold(Bold & style);
    _font.setItalic(Italic & style);
    _font.setUnderline(Underlined & style);
    _font.setStrikeOut(StrikeThrough & style);
    _coreText->setFont(_font);

    setSize(Vector2d(_coreText->boundingRect().width(), _coreText->boundingRect().height()));
    _collider->initRectangular(0, 0, _coreText->boundingRect().width(), _coreText->boundingRect().height());
#else
    _coreText.setStyle(style);
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}

void Text::setColor(Color color)
{
#ifdef IN_QT
    switch (color) {
    case Black:
        _coreText->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
        break;
    case White:
        _coreText->setDefaultTextColor(QColor::fromRgb(255, 255, 255));
        break;
    case Red:
        _coreText->setDefaultTextColor(QColor::fromRgb(255, 0, 0));
        break;
    case Green:
        _coreText->setDefaultTextColor(QColor::fromRgb(0, 255, 0));
        break;
    case Blue:
        _coreText->setDefaultTextColor(QColor::fromRgb(0, 0, 255));
        break;
    case Yellow:
        _coreText->setDefaultTextColor(QColor::fromRgb(255, 255, 0));
        break;
    case Magenta:
        _coreText->setDefaultTextColor(QColor::fromRgb(255, 0, 255));
        break;
    case Cyan:
        _coreText->setDefaultTextColor(QColor::fromRgb(0, 255, 255));
        break;
    }

    setSize(Vector2d(_coreText->boundingRect().width(), _coreText->boundingRect().height()));
    _collider->initRectangular(0, 0, _coreText->boundingRect().width(), _coreText->boundingRect().height());
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
    _coreText->setPos(getAbsolutePosition().x, getAbsolutePosition().y);
#else

    _coreText.setPosition(getAbsolutePosition().x, getAbsolutePosition().y);
    _coreText.setScale(getAbsoluteScale(), getAbsoluteScale());
    Moteur2D::getInstance()->getWindow()->draw(_coreText);
#endif
    int ret = WorldElement::draw();
    return ret;
}

// Specifics Functions
#ifdef IN_QT
void Text::updateScene(QGraphicsScene * scene)
{
    if (scene) {
        scene->addItem(_coreText);
    }
    WorldElement::updateScene(scene);
}

#else

#endif
