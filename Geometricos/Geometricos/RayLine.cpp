
#include <iostream>
#include "RayLine.h"
#include "Line.h"


RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b) {}

RayLine::RayLine(const RayLine& ray)
	: SegmentLine(ray) {}

RayLine::~RayLine() {}


bool RayLine::intersect(Line l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return 0 <= s;
	}
	return false;
}

bool RayLine::intersect(RayLine l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return 0 <= s && 0 <= t;
	}
	return false;
}

bool RayLine::intersect(SegmentLine l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return 0 <= s && (0 <= t && t <= 1);
	}
	return false;
}

RayLine& RayLine::operator=(const RayLine& rayline) {
	if (this != &rayline) {
		SegmentLine::operator=(rayline);
	}

	return *this;
}

void RayLine::out() {
	std::cout << "RayLine: ";
	SegmentLine::out();
}