
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
        BS_OVER,
        BS_DOWN,
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
    std::string _texturePathStateOver;
    Vector2d    _subRectPosStateOver;
    Vector2d    _subRectSizeStateOver;

    Text *_textOnButton;

public:
    // Constructor for text only, no image used for the button
    Button(std::string textOnButton = std::string(""));
    // Constructor with only one texture = no animation on button. Text optionnal
    Button(std::string texturePath, Vector2d subRectPos, Vector2d subRectSize, std::string textOnButton = std::string(""));
    // Constructor with two textures = the second texture is apply when button is "Down". Text optionnal
    Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
           std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown,
           std::string textOnButton = std::string(""));
    // Constructor with two textures = the third texture is apply when the button is selected or the mouse is over the button. Text optionnal
    Button(std::string texturePathStateUp, Vector2d subRectPosStateUp, Vector2d subRectSizeStateUp,
           std::string texturePathStateDown, Vector2d subRectPosStateDown, Vector2d subRectSizeStateDown,
           std::string texturePathStateOver, Vector2d subRectPosStateOver, Vector2d subRectSizeStateOver,
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
