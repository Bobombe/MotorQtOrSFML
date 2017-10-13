
#include "MouseAndKeyListener.h"

MouseAndKeyListener::MouseAndKeyListener()
{
    // TODO Auto-generated constructor stub

}

MouseAndKeyListener::~MouseAndKeyListener()
{
    // TODO Auto-generated destructor stub
}

int MouseAndKeyListener::getScreenId()
{
    return _screenIdMouse;
}
void MouseAndKeyListener::setScreenId(int screenId)
{
    _screenIdMouse = _screenIdKeyboard = screenId;
}

