
#include "KeyboardListener.h"
#include "moteur2d.h"

KeyboardListener::KeyboardListener()
{
    _id = Moteur2D::getInstance()->addKeyboardListener(this);
}

KeyboardListener::~KeyboardListener()
{
    Moteur2D::getInstance()->deleteKeyboardListener(_id);
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
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
            break;
        case Qt::Key_Escape :
            key = Key::Num0;
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
        case Qt::Key_Escape :
            key = Key::Escape;
            break;
        case Qt::Key_Escape :
            key = Key::Escape;
            break;
        case Qt::Key_Escape :
            key = Key::Escape;
            break;
        }
    }

    return key;
}
#else

#endif
