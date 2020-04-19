
#ifndef SRC_MOT_RECTANGLE_H_
#define SRC_MOT_RECTANGLE_H_

#include "Vector2d.h"
class Rectangle
{

public:
    double x;
    double y;
    double w;
    double h;

public:
	Rectangle();
	Rectangle(Vector2d pos, Vector2d size);
	Rectangle(double x, double y, double width, double height);
	virtual ~Rectangle();

    Vector2d pos();

	Vector2d size();
    double& width();
    double& height();

	void setPos(Vector2d pos);
    void setPos(double posx, double posy);

	void setSize(Vector2d size);
	void setSize(double width, double height);
};

#endif
