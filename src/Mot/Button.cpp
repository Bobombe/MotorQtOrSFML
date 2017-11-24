
#include "Button.h"

Button::Button() : _buttonState(BS_UP), _activated(0)
{
}

Button::Button(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize) :
        Sprite(texturePath, subRectPos, subRectSize),
        _buttonState(BS_UP),
        _activated(0),
        _texturePathStateUp(texturePath),
        _subRectPosStateUp(subRectPos),
        _subRectSizeStateUp(subRectSize)
{

}

Button::Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
        std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown) :
                Sprite(texturePathStateUp, subRectPosStateUp, subRectSizeStateUp),
                _buttonState(BS_UP),
                _activated(0),
                _texturePathStateUp(texturePathStateUp),
                _subRectPosStateUp(subRectPosStateUp),
                _subRectSizeStateUp(subRectSizeStateUp),
                _texturePathStateDown(texturePathStateDown),
                _subRectPosStateDown(subRectPosStateDown),
                _subRectSizeStateDown(subRectSizeStateDown)
{

}

Button::~Button()
{
}

void Button::buttonPressed(MouseButton::MouseButton button, Vector2d pos)
{
    if (posOverButton(pos)) {
        if (_buttonState == BS_HOVER) {
            _buttonState = BS_SELECTED;
            swichTexture();
        }
    }
}
void Button::buttonReleased(MouseButton::MouseButton button, Vector2d pos)
{
    if (posOverButton(pos)) {
        if (_buttonState == BS_SELECTED) {
            _activated = 2;// Activate button during 2 frames
            _buttonState = BS_UP;
            swichTexture();
        }
    }
    _buttonState = BS_UP;
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

    if (pos.x >=_absolutePos.x && pos.y >= _absolutePos.y &&
            pos.x <=_absolutePos.x + _size.x && pos.y <= _absolutePos.y + _size.y) {
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
    return _activated>0;
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

int Button::draw(Vector2d pos)
{
    if (_activated>0) {
        _activated--;
    }
    _absolutePos = pos+_pos;
    return Sprite::draw(pos);
}
