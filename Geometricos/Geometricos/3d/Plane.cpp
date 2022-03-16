
#include <iostream>
#include "Plane.h"
#include "../BasicGeometry.h"


Plane::Plane(Vect3d& p, Vect3d& u, Vect3d& v, bool arePoints) {
	if (!arePoints)			// Vectors: pi = p + u * lambda + v * mu 
	{
		_a = p;
		_b = u.add(_a);
		_c = v.add(_a);
	} else {						// 3 points in the plane.
		_a = p;
		_b = u;
		_c = v;
	}
}

Plane::Plane(const Plane& plane)
	: _a(plane._a), _b(plane._b), _c(plane._c) {
}

Plane::~Plane() {
}

bool Plane::coplanar(Vect3d& point) {
	return BasicGeometry::equal(distance(point), BasicGeometry::ZERO);
}

double Plane::distance(const Vect3d& point) {
	Vect3d normal = getNormal();

	return -(normal.dot(point) + getD()) / (normal.dot(normal));
}

double Plane::getA() {
	return (BasicGeometry::determinant2x2(_c.getZ() - _a.getZ(), _c.getY() - _a.getY(), _b.getZ() - _a.getZ(), _b.getY() - _a.getY()));
}

double Plane::getB() {
	return (BasicGeometry::determinant2x2(_c.getX() - _a.getX(), _c.getZ() - _a.getZ(), _b.getX() - _a.getX(), _b.getZ() - _a.getZ()));
}

double Plane::getC() {
	return (BasicGeometry::determinant2x2(_c.getY() - _a.getY(), _c.getX() - _a.getX(), _b.getY() - _a.getY(), _b.getX() - _a.getX()));
}

Vect3d Plane::getNormal() {
	return Vect3d(getA(), getB(), getC());
}


bool Plane::intersect(Plane& plane, Line3d& line) {
	Vect3d n1 = this->getNormal();
	Vect3d n2 = plane.getNormal();
	Vect3d n3 = n1.xProduct(n2);

	const float det = BasicGeometry::determinant3x3(n1.getX(), n1.getY(), n1.getZ(), n2.getX(), n2.getY(), n2.getZ(), n3.getX(), n3.getY(), n3.getZ());
	if (BasicGeometry::equal(BasicGeometry::ZERO, det))
		return false;

	float d1 = this->getD();
	float d2 = plane.getD();
	double x = (d2 * BasicGeometry::determinant2x2(n1.getY(), n3.getY(), n1.getZ(), n3.getZ()) - d1 * BasicGeometry::determinant2x2(n2.getY(), n3.getY(), n2.getZ(), n3.getZ())) / det;
	double y = (d2 * BasicGeometry::determinant2x2(n3.getX(), n1.getX(), n3.getZ(), n1.getZ()) - d1 * BasicGeometry::determinant2x2(n3.getX(), n2.getX(), n3.getZ(), n2.getZ())) / det;
	double z = (d2 * BasicGeometry::determinant2x2(n1.getX(), n3.getX(), n1.getY(), n3.getY()) - d1 * BasicGeometry::determinant2x2(n2.getX(), n3.getX(), n2.getY(), n3.getY())) / det;

	Vect3d orig(x, y, z);
	Vect3d dest(x + n3.getX(), y + n3.getY(), z + n3.getZ());
	line.setOrigin(orig);
	line.setDestination(dest);
	return true;
}

Vect3d Plane::projectedPoint(const Vect3d& point) {
	float r = this->distance(point);
	Vect3d normal = this->getNormal().normalize();

	return point.sub(normal.scalarMul(r));
}

PointCloud3d Plane::projectedCloud(PointCloud3d& cloud) {
	PointCloud3d newCloud;
	auto points = cloud.getPoints();
	for (auto& point : points) {
		Vect3d newPoint = this->projectedPoint(point);
		newCloud.addPoint(newPoint);
	}
	return newCloud;
}

bool Plane::intersect(Line3d& line, Vect3d& point) {
	Vect3d n(getNormal());
	Vect3d orig(line.getOrigin());
	Vect3d v(line.getDestination());
	v = v.sub(orig);
	float dot = n.dot(v);
	if (BasicGeometry::equal(BasicGeometry::ZERO, dot))
		return false;
	float lambda = -(n.dot(orig) + getD()) / dot;
	point = line.getPoint(lambda);
	return true;
}

bool Plane::intersect(Plane& pa, Plane& pb, Vect3d& pinter) {

	Vect3d a(this->getA(), pa.getA(), pb.getA());
	Vect3d b(this->getB(), pa.getB(), pb.getB());
	Vect3d c(this->getC(), pa.getC(), pb.getC());
	Vect3d d(this->getD(), pa.getD(), pb.getD());

	float det = BasicGeometry::determinant3x3(a, b, c);
	if (BasicGeometry::equal(BasicGeometry::ZERO, det))
		return false;
	pinter.setX(-BasicGeometry::determinant3x3(d, b, c) / det);
	pinter.setY(-BasicGeometry::determinant3x3(a, d, c) / det);
	pinter.setZ(-BasicGeometry::determinant3x3(a, b, d) / det);

	return true;

}



Plane& Plane::operator=(const Plane& plane) {
	if (this != &plane) {
		_a = plane._a;
		_b = plane._b;
		_c = plane._c;
	}

	return *this;
}

void Plane::out() {
	std::cout << "Plane->a: ";
	_a.out();
	std::cout << "Plane->b: ";
	_b.out();
	std::cout << "Plane->c: ";
	_c.out();
}