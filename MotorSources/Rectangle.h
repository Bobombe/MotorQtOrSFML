
#ifndef SRC_MOT_RECTANGLE_H_
#define SRC_MOT_RECTANGLE_H_

#include "Vector2d.h"
class Rectangle
{

public:
	Vector2d _pos;
	Vector2d _size;

public:
	Rectangle();
	Rectangle(Vector2d pos, Vector2d size);
	Rectangle(double x, double y, double width, double height);
	virtual ~Rectangle();

	Vector2d pos();
	double x();
	double y();

	Vector2d size();
	double width();
	double height();

	void setPos(Vector2d pos);
	void setPos(double x, double y);

	void setSize(Vector2d size);
	void setSize(double width, double height);
};

#endif
