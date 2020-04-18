
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
public:
    struct StateConfiguration {
        StateConfiguration(std::string texturePath="", Vector2d subRectPos=Vector2d(0, 0), Vector2d subRectSize=Vector2d(0, 0),
                           std::string textOnButton="", Text::Color color=Text::Color::Black):
            _texturePath(texturePath),
            _subRectPos(subRectPos),
            _subRectSize(subRectSize),
            text(textOnButton),
            textColor(color){}

        std::string _texturePath{""};
        Vector2d    _subRectPos{0,0};
        Vector2d    _subRectSize{0,0};
        std::string text{""};
        Text::Color textColor{Text::Color::Black};
    };

protected:
    static const int MAX_SIZE = 9999999;
    enum ButtonState
    {
        BS_UP,
        BS_OVER,
        BS_DOWN,
        BS_PENDING
    };

    ButtonState _buttonState;
    int         _activated;
    StateConfiguration _upConfig;
    StateConfiguration _downConfig;
    StateConfiguration _overConfig;

    Rectangle _boundingRectangle={MAX_SIZE, MAX_SIZE, 0, 0};

    Text _textOnButton;

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
    Button(StateConfiguration upConfig, StateConfiguration downConfig, StateConfiguration overConfig);

    virtual ~Button();

    virtual void buttonPressed(MouseButton::MouseButton button, Vector2d pos);
    virtual void buttonReleased(MouseButton::MouseButton button, Vector2d pos);
    virtual void mouseMoved(Vector2d pos);

    bool posOverButton(Vector2d pos);

    bool isPushed();
    bool isActivated();

    virtual void setVisible(bool visible = true);

protected:
    void swichTexture();
    void setText(std::string text);
    void setTextColor(Text::Color c);
    virtual int draw();

};

#endif
