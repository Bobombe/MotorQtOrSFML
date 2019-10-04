
#include "KeyboardListener.h"
#include "moteur2d.h"

KeyboardListener::KeyboardListener(): _screenIdKeyboard(-1)
{
    _id = Moteur2D::getInstance()->addKeyboardListener(this);
}

KeyboardListener::~KeyboardListener()
{
    Moteur2D::getInstance()->deleteKeyboardListener(_id);
}

int KeyboardListener::getScreenIdKeyboard()
{
    return _screenIdKeyboard;
}
void KeyboardListener::setScreenIdKeyboard(int screenId)
{
    _screenIdKeyboard = screenId;
}


#ifdef IN_QT
Key::Key KeyboardListener::retrieveKeyFromQt(int k)
{
    Key::Key key = Key::Unknown;

    if (k>=Qt::Key_A && k<=Qt::Key_Z)
    {
        key = Key::Key(k-65);
    }
    else if (k>=Qt::Key_0 && k<=Qt::Key_9)
    {
        key = Key::Key(Key::Numpad0 + k-Qt::Key_0);
    }
    else
    {
        switch (k)
        {
        case Qt::Key_Agrave :
            key = Key::Num0;
            break;
        case Qt::Key_Ampersand :
            key = Key::Num1;
            break;
        case Qt::Key_Eacute :
            key = Key::Num2;
            break;
        case Qt::Key_QuoteDbl :
            key = Key::Num3;
            break;
        case Qt::Key_Apostrophe :
            key = Key::Num4;
            break;
        case Qt::Key_ParenLeft :
            key = Key::Num5;
            break;
        case Qt::Key_Minus :
            key = Key::Num6;
            break;
        case Qt::Key_Egrave :
            key = Key::Num7;
            break;
        case Qt::Key_Underscore :
            key = Key::Num8;
            break;
        case Qt::Key_Ccedilla :
            key = Key::Num9;
            break;
        case Qt::Key_Escape :
            key = Key::Escape;
            break;
        case Qt::Key_Control :
            key = Key::LControl;
            break;
        case Qt::Key_Shift :
            key = Key::LShift;
            break;
        case Qt::Key_Alt :
            key = Key::LAlt;
            break;
        case Qt::Key_Hyper_L :
            key = Key::LSystem;
            break;
        case Qt::Key_Hyper_R :
            key = Key::RSystem;
            break;
        case Qt::Key_Menu :
            key = Key::Menu;
            break;
        case Qt::Key_Space :
            key = Key::Space;
            break;
        case Qt::Key_Return :
            key = Key::Return;
            break;
        case Qt::Key_Backspace :
            key = Key::BackSpace;
            break;
        case Qt::Key_Tab :
            key = Key::Tab;
            break;
        case Qt::Key_Left :
            key = Key::Left;
            break;
        case Qt::Key_Right :
            key = Key::Right;
            break;
        case Qt::Key_Up :
            key = Key::Up;
            break;
        case Qt::Key_Down :
            key = Key::Down;
            break;
        default:
        	key = Key::Unknown;
        }
    }

    return key;
}
#else

#endif
