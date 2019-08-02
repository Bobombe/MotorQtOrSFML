
#include "Button.h"

Button::Button(std::string textOnButton):
    _buttonState(BS_UP), _activated(0), _textOnButton(0)
{
    _weName = "Button";
    if (!textOnButton.empty()) {
        _textOnButton = new Text(textOnButton, this);
        Vector2d buttonSize = getSize();
        Vector2d textSize = _textOnButton->getSize();
        _textOnButton->setPosition((buttonSize - textSize) / 2);
    }
}

Button::Button(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, std::string textOnButton):
    Sprite(texturePath, subRectPos, subRectSize),
    _buttonState(BS_UP),
    _activated(0),
    _texturePathStateUp(texturePath),
    _subRectPosStateUp(subRectPos),
    _subRectSizeStateUp(subRectSize), _textOnButton(0)
{
    _weName = "Button";
    if (!textOnButton.empty()) {
        _textOnButton = new Text(textOnButton, this);
        Vector2d buttonSize = getSize();
        Vector2d textSize = _textOnButton->getSize();
        _textOnButton->setPosition((buttonSize - textSize) / 2);
    }

}

Button::Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
               std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown, std::string textOnButton):
    Sprite(texturePathStateUp, subRectPosStateUp, subRectSizeStateUp),
    _buttonState(BS_UP),
    _activated(0),
    _texturePathStateUp(texturePathStateUp),
    _subRectPosStateUp(subRectPosStateUp),
    _subRectSizeStateUp(subRectSizeStateUp),
    _texturePathStateDown(texturePathStateDown),
    _subRectPosStateDown(subRectPosStateDown),
    _subRectSizeStateDown(subRectSizeStateDown), _textOnButton(0)
{

    _weName = "Button";
    if (!textOnButton.empty()) {
        _textOnButton = new Text(textOnButton, this);
        Vector2d buttonSize = getSize();
        Vector2d textSize = _textOnButton->getSize();
        _textOnButton->setPosition((buttonSize - textSize) / 2);
    }
}

Button::~Button()
{
}

void Button::buttonPressed(MouseButton::MouseButton, Vector2d pos)
{
    if (posOverButton(pos)) {
        if (_buttonState == BS_HOVER) {
            _buttonState = BS_SELECTED;
            swichTexture();
        }
    }
}
void Button::buttonReleased(MouseButton::MouseButton, Vector2d pos)
{
    if (posOverButton(pos) && _buttonState == BS_SELECTED) {
        _activated = 1;    // Activate button during 2 frames
        _buttonState = BS_HOVER;
        swichTexture();
    } else {
        _buttonState = BS_UP;
    }
}
void Button::mouseMoved(Vector2d pos)
{
    if (posOverButton(pos)) {
        if (_buttonState == BS_UP) {
            _buttonState = BS_HOVER;
        } else if (_buttonState == BS_PENDING) {
            _buttonState = BS_SELECTED;
            swichTexture();
        }
    } else {
        if (_buttonState == BS_HOVER) {
            _buttonState = BS_UP;
        } else if (_buttonState == BS_SELECTED) {
            _buttonState = BS_PENDING;
            swichTexture();
        }
    }
}
bool Button::posOverButton(Vector2d pos)
{
    bool retValue = false;

    if (pos.x >= getAbsolutePosition().x && pos.y >= getAbsolutePosition().y &&
        pos.x <= (getAbsolutePosition().x + getAbsoluteSize().x) && pos.y <= (getAbsolutePosition().y + getAbsoluteSize().y)) {
        retValue = true;
    }

    return retValue;
}

bool Button::isPushed()
{
    return _buttonState == BS_SELECTED;
}

bool Button::isActivated()
{
    return _visible && (_activated > 0);
}

void Button::setVisible(bool visible)
{
    _visible = visible;
    _textOnButton->setVisible(visible);
}

void Button::swichTexture()
{
    if (!_texturePathStateDown.empty()) {
        if (_buttonState == BS_SELECTED) {
            setSprite(_texturePathStateDown, _subRectPosStateDown, _subRectSizeStateDown);
        } else {
            setSprite(_texturePathStateUp, _subRectPosStateUp, _subRectSizeStateUp);
        }
    }
}

int Button::draw()
{
    if (_activated > 0) {
        _activated--;
    }
    return Sprite::draw();
}
