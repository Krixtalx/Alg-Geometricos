#include "Vect2d.h"


Vect2d::Vect2d(const Point& point)
	: Point(point)
{
}

Vect2d::Vect2d(const Vect2d& v)
	: Point(v._x, v._y)
{
}

Vect2d::~Vect2d()
{
}

Vect2d Vect2d::add(Vect2d& b)
{
	return Vect2d(this->_x + b._x, this->_y + b._y);
}

double Vect2d::dot(Vect2d& b)
{
	return this->_x * b._x + this->_y * b._y;
}

Vect2d& Vect2d::operator=(const Vect2d& vector)
{
	Point::operator=(vector);

	return *this;
}

Vect2d Vect2d::scalarMult(double t)
{
	return Vect2d(this->_x * t, this->_y * t);
}

Vect2d Vect2d::sub(Vect2d& b)
{
	return Vect2d(this->_x - b._x, this->_y - b._y);
}
