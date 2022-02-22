
#include <iostream>
#include "Line.h"
#include "RayLine.h"
#include "SegmentLine.h"


Line::Line(const Point& a, const Point& b)
	: SegmentLine(a, b) {}

Line::Line(const Line& s)
	: SegmentLine(s) {}

Line::~Line() {}

bool Line::intersect(Line l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return true;
	}
	return false;
}

bool Line::intersect(RayLine l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return 0 <= t;
	}
	return false;
}

bool Line::intersect(SegmentLine l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return (0 <= t && t <= 1);
	}
	return false;
}


Line& Line::operator=(const Line& line) {
	if (this != &line) {
		SegmentLine::operator=(line);
	}

	return *this;
}


void Line::out() {
	std::cout << "Line: ";
	std::cout << "Point A: ";
	this->_orig.out();
	std::cout << "Point B: ";
	this->_dest.out();
}
