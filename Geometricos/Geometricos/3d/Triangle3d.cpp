
#include <iostream>
#include <cmath>
#include "../BasicGeometry.h"
#include "Triangle3d.h"
#include "Edge3d.h"


Triangle3d::Triangle3d() {
}

Triangle3d::Triangle3d(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
	: _a(ax, ay, az), _b(bx, by, bz), _c(cx, cy, cz) {
}

Triangle3d::Triangle3d(const Triangle3d& triangle)
	: _a(triangle._a), _b(triangle._b), _c(triangle._c) {
}

Triangle3d::Triangle3d(Vect3d& va, Vect3d& vb, Vect3d& vc)
	: _a(va), _b(vb), _c(vc) {
}

Triangle3d::~Triangle3d() {
}

double Triangle3d::area() {
	Vect3d AB = _a.sub(_b);
	Vect3d AC = _a.sub(_c);

	return AB.xProduct(AC).module() / 2;

}

Triangle3d::PointPosition Triangle3d::classify(Vect3d& point) {
	Vect3d v = point.sub(_a);
	double len = v.module();

	if (BasicGeometry::equal(len, BasicGeometry::ZERO))
		return PointPosition::COPLANAR;

	v = v.scalarMul(1 / len);
	Vect3d normal = this->normal();
	double d = v.dot(normal);
	if (d > BasicGeometry::ZERO)
		return PointPosition::POSITIVE;
	if (d < BasicGeometry::ZERO)
		return PointPosition::NEGATIVE;

	return PointPosition::COPLANAR;
}



Vect3d Triangle3d::normal() {
	Vect3d v1(_b.sub(_a));
	Vect3d v2(_c.sub(_a));
	Vect3d n(v1.xProduct(v2));
	double module = n.module();

	return (n.scalarMul(1.0f / module));
}

Triangle3d& Triangle3d::operator=(const Triangle3d& triangle) {
	_a = triangle._a;
	_b = triangle._b;
	_c = triangle._c;

	return *this;
}

void Triangle3d::out() {
	std::cout << "Triangle 3D: ";
	_a.out();
	_b.out();
	_c.out();
}



void Triangle3d::set(Vect3d& va, Vect3d& vb, Vect3d& vc) {
	_a = va;
	_b = vb;
	_c = vc;
}

