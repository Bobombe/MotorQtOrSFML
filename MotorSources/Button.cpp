
#include "Button.h"

Button::Button(std::string textOnButton):
    _buttonState(BS_UP), _activated(0), _textOnButton(Text(textOnButton, this))
{
    _weName = "Button";
    _upConfig.text = textOnButton;
    _downConfig.text = textOnButton;
    _overConfig.text = textOnButton;
    setText(textOnButton);
}

Button::Button(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, std::string textOnButton):
    Sprite(texturePath, subRectPos, subRectSize),
    _buttonState(BS_UP),
    _activated(0),
    _upConfig(texturePath, subRectPos, subRectSize, textOnButton),
    _textOnButton(Text(textOnButton, this))
{
    _weName = "Button";
    setText(textOnButton);

}

Button::Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
               std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown, std::string textOnButton):
    Sprite(texturePathStateUp, subRectPosStateUp, subRectSizeStateUp),
    _buttonState(BS_UP),
    _activated(0),
    _upConfig{texturePathStateUp, subRectPosStateUp, subRectSizeStateUp, textOnButton},
    _downConfig{texturePathStateDown, subRectPosStateDown, subRectSizeStateDown, textOnButton},
    _textOnButton(Text(textOnButton, this))
{

    _weName = "Button";
    setText(textOnButton);
}

Button::Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
               std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown,
               std::string texturePathStateOver, Vector2d subRectPosStateOver, Vector2d subRectSizeStateOver, std::string textOnButton):
    Sprite(texturePathStateUp, subRectPosStateUp, subRectSizeStateUp),
    _buttonState(BS_UP),
    _activated(0),
    _upConfig{texturePathStateUp, subRectPosStateUp, subRectSizeStateUp, textOnButton},
    _downConfig{texturePathStateDown, subRectPosStateDown, subRectSizeStateDown, textOnButton},
    _overConfig{texturePathStateOver, subRectPosStateOver, subRectSizeStateOver, textOnButton},
    _textOnButton(Text(textOnButton, this))
{

    _weName = "Button";
    setText(textOnButton);
}

Button::Button(Button::StateConfiguration upConfig, Button::StateConfiguration downConfig, Button::StateConfiguration overConfig):
    Sprite(upConfig._texturePath, upConfig._subRectPos, upConfig._subRectSize),
    _buttonState(BS_UP),
    _activated(0),
    _upConfig(upConfig),
    _downConfig(downConfig),
    _overConfig(overConfig),
    _textOnButton(Text(upConfig.text, this))
{
    _weName = "Button";
    setText(upConfig.text);
    setTextColor(upConfig.textColor);
}

Button::~Button()
{
}

void Button::buttonPressed(MouseButton::MouseButton, Vector2d pos)
{
    if (posOverButton(pos)) {
        if (_buttonState == BS_OVER) {
            _buttonState = BS_DOWN;
            swichTexture();
        }
    }
}
void Button::buttonReleased(MouseButton::MouseButton, Vector2d pos)
{
    if (posOverButton(pos) && _buttonState == BS_DOWN) {
        _activated = 1;    // Activate button during 2 frames
        _buttonState = BS_OVER;
        swichTexture();
    } else {
        _buttonState = BS_UP;
    }
}
void Button::mouseMoved(Vector2d pos)
{
    if (posOverButton(pos)) {
        if (_buttonState == BS_UP) {
            _buttonState = BS_OVER;
            swichTexture();
        } else if (_buttonState == BS_PENDING) {
            _buttonState = BS_DOWN;
            swichTexture();
        }
    } else {
        if (_buttonState == BS_OVER) {
            _buttonState = BS_UP;
            swichTexture();
        } else if (_buttonState == BS_DOWN) {
            _buttonState = BS_PENDING;
            swichTexture();
        }
    }
}
bool Button::posOverButton(Vector2d pos)
{
    bool retValue = false;
    static const double epsilon{0.001};
    // We get most top-left position between Sprite and text objects.
    Rectangle buttonBBox(getBoundingBox());
    if (buttonBBox.x < epsilon || buttonBBox.y < epsilon) { // if sprite size null, we take text boundaries
        buttonBBox = _textOnButton.getBoundingBox();
    }

    // We compare to last bounding rectangle _boundingRectangle
    if (_boundingRectangle.x>buttonBBox.x) {
        _boundingRectangle.x=buttonBBox.x;
    }
    if (_boundingRectangle.y>buttonBBox.y) {
        _boundingRectangle.y=buttonBBox.y;
    }
    if (_boundingRectangle.w<buttonBBox.width()) {
        _boundingRectangle.w=buttonBBox.width();
    }
    if (_boundingRectangle.h<buttonBBox.height()) {
        _boundingRectangle.h=buttonBBox.height();
    }

    Vector2d posPrim(_boundingRectangle.pos());
    Vector2d relPos = pos-posPrim;
    relPos.rotateInDegree(-getRotation());
    posPrim=posPrim+relPos;
    // Now we check if position is in the the previousli created rectangle
    if (posPrim.x >= _boundingRectangle.x && posPrim.y >= _boundingRectangle.y &&
        posPrim.x <= (_boundingRectangle.x + _boundingRectangle.w) && posPrim.y <= (_boundingRectangle.y + _boundingRectangle.h)) {
        retValue = true;
    } else {
        _boundingRectangle={MAX_SIZE, MAX_SIZE, 0, 0}; // resume last bounding when leaving button.
    }

    return retValue;
}

bool Button::isPushed()
{
    return _buttonState == BS_DOWN;
}

bool Button::isActivated()
{
    return _visible && (_activated > 0);
}

void Button::setVisible(bool visible)
{
    _visible = visible;
    _textOnButton.setVisible(visible);
}

void Button::setText(std::string text)
{
    _textOnButton.setText(text);
    if (!text.empty()) {
        Vector2d buttonSize = getSize();
        Vector2d textSize = _textOnButton.getSize();
        _textOnButton.setPosition(((buttonSize - textSize) / 2) - getRefPoint());
    }
}

void Button::setTextColor(Color c)
{
    _textOnButton.setColor(c);
}

void Button::swichTexture()
{
    switch (_buttonState) {
    case BS_DOWN:
        if (!_downConfig._texturePath.empty()) {
            setSprite(_downConfig._texturePath, _downConfig._subRectPos, _downConfig._subRectSize);
        }
        setText(_downConfig.text);
        setTextColor(_downConfig.textColor);
        break;
    case BS_OVER:
        if (!_overConfig._texturePath.empty()) {
            setSprite(_overConfig._texturePath, _overConfig._subRectPos, _overConfig._subRectSize);
        }
        setText(_overConfig.text);
        setTextColor(_overConfig.textColor);
        break;
    default:
        if (!_upConfig._texturePath.empty()) {
            setSprite(_upConfig._texturePath, _upConfig._subRectPos, _upConfig._subRectSize);
        }
        setText(_upConfig.text);
        setTextColor(_upConfig.textColor);
        _boundingRectangle={MAX_SIZE, MAX_SIZE, 0, 0}; // resume last bounding when leaving button.
        break;
    }
}

int Button::draw()
{
    if (_activated > 0) {
        _activated--;
    }
    return Sprite::draw();
}
