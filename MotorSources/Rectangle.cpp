
#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Vector2d pos, Vector2d size)
{
    setPos(pos);
    setSize(size);
}

Rectangle::Rectangle(double x, double y, double width, double height)
{
    setPos(x, y);
    setSize(width, height);
}

Rectangle::~Rectangle()
{
}

Vector2d Rectangle::pos()
{
    return Vector2d(x, y);
}

Vector2d Rectangle::size()
{
    return Vector2d(w, h);
}
double& Rectangle::width()
{
    return w;
}
double& Rectangle::height()
{
    return h;
}

void Rectangle::setPos(Vector2d pos)
{
    x = pos.x;
    y = pos.y;
}
void Rectangle::setPos(double posx, double posy)
{
    x = posx;
    y = posy;
}

void Rectangle::setSize(Vector2d size)
{
    w = size.x;
    h = size.y;
}
void Rectangle::setSize(double width, double height)
{
    w = width;
    h = height;
}

