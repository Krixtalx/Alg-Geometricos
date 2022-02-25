#include <cmath>
#include <iostream>
#include <string>
#include "Point.h"
#include "BasicGeometry.h"


using namespace std;

Point::Point()
{
	_x = DEFAULT_VALUE;
	_y = DEFAULT_VALUE;
}

Point::Point(double x, double y, bool polar)
{
	if (!polar) {
		_x = x;
		_y = y;
	} else {
		_x = y * cos(x);
		_y = y * sin(x);
	}
}

Point::Point(const Point& point)
{
	_x = point._x;
	_y = point._y;
}

Point::~Point()
{
}

Point::PointClassification Point::classify(Point& p0, Point& p1)
{
	Point a = p1.minus(p0);
	Point b = this->minus(p0);
	double sa = triangleArea2(p0, p1);
	if (sa < 0.0f) return PointClassification::RIGHT;
	if (sa > 0.0f) return PointClassification::LEFT;
	if (p0.equal(*this)) return PointClassification::ORIGIN;
	if (p1.equal(*this)) return PointClassification::DEST;
	if (a.getModule() < b.getModule()) return PointClassification::FORWARD;
	if ((a._x * b._x < 0) || (a._y * b._y < 0)) return PointClassification::BACKWARD;
	return PointClassification::BETWEEN;
}

bool Point::colinear(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result != PointClassification::LEFT) && (result != PointClassification::RIGHT);
}

double Point::distPoint(Point& p)
{
	return std::sqrt(std::pow(p._x - _x, 2) + std::pow(p._y - _y, 2));
}

double Point::getAlpha()
{
	return std::atan2(_y, _x);
}


double Point::getModule()
{
	return std::sqrt(std::pow(_x, 2) + std::pow(_y, 2));
}

bool Point::leftAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::LEFT) || (result != PointClassification::RIGHT);
}

Point& Point::operator=(const Point& point)
{
	_x = point._x;
	_y = point._y;

	return *this;
}

bool Point::rightAbove(Point& a, Point& b)
{
	PointClassification result = classify(a, b);
	return (result == PointClassification::RIGHT) || (result != PointClassification::LEFT);
}

double Point::slope(Point& p)
{
	if (BasicGeometry::equal(p._x, this->_x)) return BasicGeometry::INFINITO;
	return (p._y - this->_y) / (p._x - this->_x);
}

Point Point::add(const Point& other)
{
	return Point(this->_x + other._x, this->_y + other._y);
}

Point Point::minus(const Point& other)
{
	return Point(this->_x - other._x, this->_y - other._y);
}

void Point::out()
{
	string outstring = "Coordinate x: " + std::to_string(_x) + ", coordinate y: " + std::to_string(_y);
	cout << outstring << endl;;
}
