
#include <iostream>
#include "RayLine.h"
#include "Line.h"


RayLine::RayLine(const Point& a, const Point& b)
	: SegmentLine(a, b) {}

RayLine::RayLine(const RayLine& ray)
	: SegmentLine(ray) {}

RayLine::~RayLine() {}

float RayLine::distPointRayline(Vect2d& v)
{
	Vect2d d = _dest.minus(_orig);
	Vect2d aMinusP = v.minus(_orig);
	float t0 = (d.dot(aMinusP)) / d.dot(d);
	Vect2d aux(_orig.add(d.scalarMult(t0)));
	if (t0 <= 0)
		return aMinusP.getModule();
	return v.sub(aux).getModule();
}


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