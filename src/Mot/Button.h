
#ifndef SRC_MOT_BUTTON_H_
#define SRC_MOT_BUTTON_H_

#include "Sprite.h"
#include "Vector2d.h"
#include "Rectangle.h"
#include "MouseAndKeyListener.h"
#include "Text.h"

#include <map>
#include <vector>

class Button: public Sprite, public MouseAndKeyListener
{

protected:
    enum ButtonState
    {
        BS_UP,
        BS_HOVER,
        BS_SELECTED,
        BS_PENDING
    };

    ButtonState _buttonState;
    int         _activated;
    std::string _texturePathStateUp;
    Vector2d    _subRectPosStateUp;
    Vector2d    _subRectSizeStateUp;
    std::string _texturePathStateDown;
    Vector2d    _subRectPosStateDown;
    Vector2d    _subRectSizeStateDown;

    Text *_textOnButton;

public:
    Button(std::string textOnButton = std::string(""));
    Button(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, std::string textOnButton = std::string(""));
    Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
           std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown,
           std::string textOnButton = std::string(""));

    virtual ~Button();

    virtual void buttonPressed(MouseButton::MouseButton button, Vector2d pos);
    virtual void buttonReleased(MouseButton::MouseButton button, Vector2d pos);
    virtual void mouseMoved(Vector2d pos);

    bool posOverButton(Vector2d pos);

    bool isPushed();
    bool isActivated();

    virtual void setVisible(bool visible = true);

protected:
    void        swichTexture();
    virtual int draw();

};

#endif
