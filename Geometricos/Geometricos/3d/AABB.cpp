#include "AABB.h"
#include "Triangle3d.h"
#include <iostream>


AABB::AABB() {
}

AABB::AABB(Vect3d& min, Vect3d& max)
	: _min(min), _max(max) {
}

AABB::AABB(const AABB& aabb)
	: _min(aabb._min), _max(aabb._max) {
}

AABB::~AABB() {
}




Vect3d AABB::getCenter() {
	return Vect3d((_min.getX() + _max.getX()) / 2, (_min.getY() + _max.getY()) / 2, (_min.getZ() + _max.getZ()) / 2);
}

Vect3d AABB::getExtent() {
	Vect3d center = getCenter();
	return _max.sub(center);
}

AABB& AABB::operator=(const AABB& orig) {
	_min = orig._min;
	_max = orig._max;

	return *this;
}
