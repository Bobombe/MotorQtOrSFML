
#include "MouseListener.h"
#include "moteur2d.h"

MouseListener::MouseListener()
{
    _id = Moteur2D::getInstance()->addMouseListener(this);
}

MouseListener::~MouseListener()
{
    Moteur2D::getInstance()->deleteMouseListener(_id);
}

