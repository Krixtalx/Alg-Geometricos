
#include <iostream>
#include <cmath>
#include "../BasicGeometry.h"
#include "Triangle3d.h"
#include "Edge3d.h"
#include "Ray3d.h"


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

Vect3d Triangle3d::operator[](const int& pos) {
	if (pos == 0)
		return _a;
	if (pos == 1)
		return _b;
	return _c;
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

bool Triangle3d::rayTri(const Ray3d& ray, Vect3d& point) {
	const float EPSILON = 0.0000001;
	Vect3d vertex0 = this->_a;
	Vect3d vertex1 = this->_b;
	Vect3d vertex2 = this->_c;
	Vect3d edge1, edge2, h, s, q;
	Vect3d rayVector = ray.getEdgeVector();
	Vect3d rayOrigin = ray.getOrigin();
	float a, f, u, v;
	edge1 = vertex1.sub(vertex0);
	edge2 = vertex2.sub(vertex0);
	h = rayVector.xProduct(edge2);
	a = edge1.dot(h);
	if (a > -EPSILON && a < EPSILON)
		return false;    // This ray is parallel to this triangle.
	f = 1.0 / a;
	s = rayOrigin.sub(vertex0);
	u = f * s.dot(h);
	if (u < 0.0 || u > 1.0)
		return false;
	q = s.xProduct(edge1);
	v = f * rayVector.dot(q);
	if (v < 0.0 || u + v > 1.0)
		return false;
	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * edge2.dot(q);
	if (t > EPSILON) // ray intersection
	{
		point = rayOrigin.add(rayVector.scalarMul(t));
		return true;
	} else // This means that there is a line intersection but not a ray intersection.
		return false;
}

