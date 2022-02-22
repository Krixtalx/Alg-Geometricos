#include <cmath>
#include <iostream>
#include "SegmentLine.h"
#include "Line.h"
#include "RayLine.h"

SegmentLine::SegmentLine() {}

SegmentLine::SegmentLine(const Point& a, const Point& b)
	: _orig(a), _dest(b) {}

SegmentLine::SegmentLine(const SegmentLine& segment)
	: _orig(segment._orig), _dest(segment._dest) {}

SegmentLine::SegmentLine(double ax, double ay, double bx, double by)
	: _orig(ax, ay), _dest(bx, by) {}

SegmentLine::~SegmentLine() {}


SegmentLine& SegmentLine::operator=(const SegmentLine& segment) {
	if (this != &segment) {
		this->_orig = segment._orig;
		this->_dest = segment._dest;
	}

	return *this;
}

bool SegmentLine::intersects(Vect2d& C, Vect2d& D, float& t, float& s) {
	Vect2d A = this->_orig;
	Vect2d B = this->_dest;
	Vect2d AB = A.minus(B);
	Vect2d AC = A.minus(C);
	Vect2d CD = C.minus(D);
	float div = (CD.getX() * AB.getY() - AB.getX() * CD.getY());
	if (BasicGeometry::equal(div, 0))
		return false;

	s = (CD.getX() * AC.getY() - AC.getX() * CD.getY()) / div;
	t = (AB.getX() * AC.getY() - AC.getX() * AB.getY()) / div;
	return true;
}

double SegmentLine::getEquC() {
	double pendiente = slope();
	if (BasicGeometry::equal(pendiente, BasicGeometry::INFINITO))
		return -BasicGeometry::INFINITO;
	return _orig.getY() - slope() * _orig.getX();
}

bool SegmentLine::distinct(SegmentLine& segment) {
	return !equal(segment);
}



float SegmentLine::distPointSegment(Vect2d& vector) {
	return 0.0f;
}

bool SegmentLine::equal(SegmentLine& segment) {
	return (_orig.equal(segment._orig) && _dest.equal(segment._dest)) || (_orig.equal(segment._dest) && _dest.equal(segment._orig));
}

Point SegmentLine::getPoint(double t) {
	Point resta(_dest.minus(_orig));
	Point resultado;
	resultado.setX(_orig.getX() + resta.getX() * t);
	resultado.setY(_orig.getY() + resta.getY() * t);
	return resultado;
}


bool SegmentLine::impSegmentIntersection(SegmentLine& segment) {
	Point a = this->_orig, b = this->_dest, c = segment._orig, d = segment._dest;

	return (a.isBetween(c, d) || b.isBetween(c, d) || c.isBetween(a, b) || d.isBetween(a, b));
}

bool SegmentLine::isHorizontal() {
	return BasicGeometry::equal(slope(), BasicGeometry::ZERO);
}




bool SegmentLine::isVertical() {
	return BasicGeometry::equal(slope(), BasicGeometry::INFINITO);
}


double SegmentLine::slope() {
	return _orig.slope(_dest);
}



// PROTECTED METHODS



void SegmentLine::out() {
	std::cout << "Point A: )";
	_orig.out();
	std::cout << "Point B: ";
	_dest.out();
}

bool SegmentLine::segmentIntersection(SegmentLine& l) {
	Point a = this->_orig, b = this->_dest, c = l._orig, d = l._dest;

	if (a.colinear(c, d) || b.colinear(c, d) || c.colinear(a, b) || d.colinear(a, b))
		return false;
	return (a.left(c, d) ^ b.left(c, d) && c.left(a, b) ^ d.left(a, b));
}

bool SegmentLine::intersect(Line l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return 0 <= s && s <= 1;
	}
	return false;

}

bool SegmentLine::intersect(RayLine l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return (0 <= s && s <= 1) && (0 <= t);
	}
	return false;
}

bool SegmentLine::intersect(SegmentLine l, Vect2d& intersec) {
	float s, t;
	Vect2d c = l.getA();
	Vect2d d = l.getB();
	if (intersects(c, d, t, s)) {
		intersec = getPoint(s);
		return (0 <= s && s <= 1) && (0 <= t && t <= 1);
	}
	return false;
}
