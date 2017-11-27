/*
 * Vector2d.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: dev
 */

#include "Vector2d.h"

#include <cmath>

#define PI 3.1416

Vector2d::Vector2d() : x(0), y(0)
{
}
Vector2d::Vector2d(double x, double y) : x(x), y(y)
{
}

Vector2d::~Vector2d()
{
}

// For calculus
double Vector2d::getNorm()
{
    return (sqrt(x*x + y*y));
}
double Vector2d::getAngleInDegree()
{
    return atan2(y, x)*180/PI;
}

void Vector2d::normalize()
{
	double norm = getNorm();
	if (norm !=0) {
		*this /= norm;
	} else {
		x = y = 0;
	}
}
void Vector2d::rotateInDegree(double angleInDegree)
{
    double norm = getNorm();
    normalize();
    double newAngle = getAngleInDegree() + angleInDegree;
    newAngle*=PI/180.;
    x = cos(newAngle);
    y = sin(newAngle);
    *this *= norm;
}

void Vector2d::toNull()
{
	x = 0;
	y = 0;
}


/////////////////////////////////////////////////////
//          Calculus operators                     //
/////////////////////////////////////////////////////
// Additions
Vector2d &Vector2d::operator+=(const double & number)
{
    double norm = getNorm();
    double newX = (x*(norm+number))/norm;
    double newY = (y*(norm+number))/norm;
    x = newX;
    y = newY;
    return *this;
}
Vector2d &Vector2d::operator+=(const Vector2d & vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}
Vector2d Vector2d::operator+(const double & number)
{
    Vector2d ret(*this);
    ret += number;
    return ret;
}
Vector2d Vector2d::operator+(const Vector2d & vec)
{
    Vector2d ret(*this);
    ret += vec;
    return ret;
}
// Subtractions
Vector2d &Vector2d::operator-=(const double & number)
{
    *this += -number;
    return *this;
}
Vector2d &Vector2d::operator-=(const Vector2d & vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}
Vector2d Vector2d::operator-(const double & number)
{
    Vector2d ret(*this);
    ret += -number;
    return ret;
}
Vector2d Vector2d::operator-(const Vector2d & vec)
{
    Vector2d ret(*this);
    ret -= vec;
    return ret;
}
Vector2d Vector2d::operator-()
{
    Vector2d ret(*this);
    ret.x = -ret.x;
    ret.y = -ret.y;
    return ret;
}
// Multiplications
Vector2d &Vector2d::operator*=(const double & number)
{
    x*=number;
    y*=number;
    return *this;
}
Vector2d Vector2d::operator*(const double & number)
{
    Vector2d ret(*this);
    ret *= number;
    return ret;
}
double Vector2d::operator*(const Vector2d & vec)
{
    return x*vec.x + y*vec.y;
}
// Divisions
Vector2d &Vector2d::operator/=(const double & number)
{
    x/=number;
    y/=number;
    return *this;
}
Vector2d Vector2d::operator/(const double & number)
{
    Vector2d ret(*this);
    ret /= number;
    return ret;
}

// Equality
bool &Vector2d::operator==(const Vector2d & vec)
{
    bool ret = false;
    if (this->x == vec.x && this->y == vec.y) {
        ret = true;
    }
    return ret;
}
