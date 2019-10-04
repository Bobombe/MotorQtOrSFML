
#include "MouseListener.h"
#include "moteur2d.h"

MouseListener::MouseListener() : _screenIdMouse(-1)
{
    _id = Moteur2D::getInstance()->addMouseListener(this);
}

MouseListener::~MouseListener()
{
    Moteur2D::getInstance()->deleteMouseListener(_id);
}

int MouseListener::getScreenIdMouse()
{
    return _screenIdMouse;
}
void MouseListener::setScreenIdMouse(int screenId)
{
    _screenIdMouse = screenId;
}

