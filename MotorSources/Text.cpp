#include "Text.h"
#include "moteur2d.h"

#ifdef IN_QT
#include <QFontDatabase>
#else
#endif

Text::Text():
    WorldElement()
{
    init("");
}
Text::Text(WorldElement *parent, int layer):
    WorldElement(parent, layer)
{
    init("");
}
Text::Text(std::string text, WorldElement *parent, int layer):
    WorldElement(parent, layer)
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

    int id = QFontDatabase::addApplicationFont("./MotorResources/OpenSans-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    _coreText = new QGraphicsTextItem();
    _coreText->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
    _font.setFamily(family);
    _font.setPixelSize(30);
    _coreText->setFont(_font);
#else
    _coreText.setFont(Moteur2D::getInstance()->getFont());
    _coreText.setCharacterSize(30);
    _coreText.setFillColor(sf::Color::White);
#endif
    setText(text);
    setParent(_parent);
    setPosition(Vector2d(0, 0));
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
    updateSize();
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
    updateSize();
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
    updateSize();
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}

void Text::setColor(Color color)
{
#ifdef IN_QT
    switch (color) {
        case Color::Black:
            _coreText->setDefaultTextColor(QColor::fromRgb(0, 0, 0));
            break;
        case Color::White:
            _coreText->setDefaultTextColor(QColor::fromRgb(255, 255, 255));
            break;
        case Color::Red:
            _coreText->setDefaultTextColor(QColor::fromRgb(255, 0, 0));
            break;
        case Color::Green:
            _coreText->setDefaultTextColor(QColor::fromRgb(0, 255, 0));
            break;
        case Color::Blue:
            _coreText->setDefaultTextColor(QColor::fromRgb(0, 0, 255));
            break;
        case Color::Yellow:
            _coreText->setDefaultTextColor(QColor::fromRgb(255, 255, 0));
            break;
        case Color::Magenta:
            _coreText->setDefaultTextColor(QColor::fromRgb(255, 0, 255));
            break;
        case Color::Cyan:
            _coreText->setDefaultTextColor(QColor::fromRgb(0, 255, 255));
            break;
    }

    setSize(Vector2d(_coreText->boundingRect().width(), _coreText->boundingRect().height()));
    _collider->initRectangular(0, 0, _coreText->boundingRect().width(), _coreText->boundingRect().height());
#else
    switch (color) {
        case Color::Black:
            _coreText.setFillColor(sf::Color::Black);
            break;
        case Color::White:
            _coreText.setFillColor(sf::Color::White);
            break;
        case Color::Red:
            _coreText.setFillColor(sf::Color::Red);
            break;
        case Color::Green:
            _coreText.setFillColor(sf::Color::Green);
            break;
        case Color::Blue:
            _coreText.setFillColor(sf::Color::Blue);
            break;
        case Color::Yellow:
            _coreText.setFillColor(sf::Color::Yellow);
            break;
        case Color::Magenta:
            _coreText.setFillColor(sf::Color::Magenta);
            break;
        case Color::Cyan:
            _coreText.setFillColor(sf::Color::Cyan);
            break;
    }
    updateSize();
    _collider->initRectangular(0, 0, _coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height);
#endif
}

int Text::draw()
{
#ifdef IN_QT
    _coreText->setPos(getAbsolutePosition().x, getAbsolutePosition().y);
    _coreText->setVisible(_visible);
#else

    _coreText.setPosition(getBoundingBox().x, getBoundingBox().y);
    _coreText.setRotation(getAbsoluteRotaion());
    _coreText.setScale(getAbsoluteScale(), getAbsoluteScale());
    Moteur2D::getInstance()->getWindow()->draw(_coreText);
#endif
    int ret = WorldElement::draw();
    return ret;
}

void Text::updateSize()
{
    _coreText.setRotation(0);
    setSize(Vector2d(_coreText.getGlobalBounds().width, _coreText.getGlobalBounds().height));
    _coreText.setRotation(getAbsoluteRotaion());
}

// Specifics Functions
#ifdef IN_QT
void Text::updateScene(QGraphicsScene *scene)
{
    if (scene) {
        scene->addItem(_coreText);
    }
    WorldElement::updateScene(scene);
}

#else

#endif
