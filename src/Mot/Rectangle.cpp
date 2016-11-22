
#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Vector2d pos, Vector2d size)
{
	_pos = pos;
	_size = size;
}

Rectangle::Rectangle(double x, double y, double width, double height)
{
	_pos.x = x;
	_pos.y = y;
	_size.x = width;
	_size.y = height;
}

Rectangle::~Rectangle()
{
}

Vector2d Rectangle::pos()
{
	return _pos;
}
double Rectangle::x()
{
	return _pos.x;
}
double Rectangle::y()
{
	return _pos.y;
}

Vector2d Rectangle::size()
{
	return _size;
}
double Rectangle::width()
{
	return _size.x;
}
double Rectangle::height()
{
	return _size.y;
}

void Rectangle::setPos(Vector2d pos)
{
	_pos = pos;
}
void Rectangle::setPos(double x, double y)
{
	_pos.x = x;
	_pos.y = y;
}

void Rectangle::setSize(Vector2d size)
{
	_size = size;
}
void Rectangle::setSize(double width, double height)
{
	_size.x = width;
	_size.y = height;
}

