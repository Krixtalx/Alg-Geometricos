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

inline int planeBoxOverlap(Vect3d normal, Vect3d vert, Vect3d maxbox) {
	int q;

	Vect3d vmin, vmax;
	float v;

	for (q = 0; q <= 2; q++) {
		v = vert[q];					// -NJMP-

		if (normal[q] > 0.0f) {
			vmin[q] = -maxbox[q] - v;	// -NJMP-

			vmax[q] = maxbox[q] - v;	// -NJMP-
		} else {
			vmin[q] = maxbox[q] - v;	// -NJMP-

			vmax[q] = -maxbox[q] - v;	// -NJMP-
		}

	}

	if (normal.dot(vmin) > 0.0f) return 0;	// -NJMP-

	if (normal.dot(vmax) >= 0.0f) return 1;	// -NJMP-



	return 0;

}

/*======================== X-tests ========================*/

inline bool axisTestX01(float a, float b, float fa, float fb, const Vect3d& v0,
	const Vect3d& v2, const Vect3d& boxhalfsize, float& rad, float& min,
	float& max, float& p0, float& p2) {
	p0 = a * v0.getY() - b * v0.getZ();
	p2 = a * v2.getY() - b * v2.getZ();
	if (p0 < p2) {
		min = p0;
		max = p2;
	} else {
		min = p2;
		max = p0;
	}
	rad = fa * boxhalfsize.getY() + fb * boxhalfsize.getZ();
	if (min > rad || max < -rad)
		return false;
	return true;
}
inline bool axisTestX2(float a, float b, float fa, float fb, const Vect3d& v0,
	const Vect3d& v1, const Vect3d& boxhalfsize, float& rad, float& min,
	float& max, float& p0, float& p1) {
	p0 = a * v0.getY() - b * v0.getZ();
	p1 = a * v1.getY() - b * v1.getZ();
	if (p0 < p1) {
		min = p0;
		max = p1;
	} else {
		min = p1;
		max = p0;
	}
	rad = fa * boxhalfsize.getY() + fb * boxhalfsize.getZ();
	if (min > rad || max < -rad)
		return false;
	return true;
}

/*======================== Y-tests ========================*/

inline bool axisTestY02(float a, float b, float fa, float fb, const Vect3d& v0,
	const Vect3d& v2, const Vect3d& boxhalfsize, float& rad, float& min,
	float& max, float& p0, float& p2) {
	p0 = -a * v0.getX() + b * v0.getZ();
	p2 = -a * v2.getX() + b * v2.getZ();
	if (p0 < p2) {
		min = p0;
		max = p2;
	} else {
		min = p2;
		max = p0;
	}
	rad = fa * boxhalfsize.getX() + fb * boxhalfsize.getZ();
	if (min > rad || max < -rad)
		return false;
	return true;
}

inline bool axisTestY1(float a, float b, float fa, float fb, const Vect3d& v0,
	const Vect3d& v1, const Vect3d& boxhalfsize, float& rad, float& min,
	float& max, float& p0, float& p1) {
	p0 = -a * v0.getX() + b * v0.getZ();
	p1 = -a * v1.getX() + b * v1.getZ();
	if (p0 < p1) {
		min = p0;
		max = p1;
	} else {
		min = p1;
		max = p0;
	}
	rad = fa * boxhalfsize.getX() + fb * boxhalfsize.getZ();
	if (min > rad || max < -rad)
		return false;
	return true;
}

/*======================== Z-tests ========================*/
inline bool axisTestZ12(float a, float b, float fa, float fb, const Vect3d& v1,
	const Vect3d& v2, const Vect3d& boxhalfsize, float& rad, float& min,
	float& max, float& p1, float& p2) {
	p1 = a * v1.getX() - b * v1.getY();
	p2 = a * v2.getX() - b * v2.getY();
	if (p1 < p2) {
		min = p1;
		max = p2;
	} else {
		min = p2;
		max = p1;
	}
	rad = fa * boxhalfsize.getX() + fb * boxhalfsize.getY();
	if (min > rad || max < -rad)
		return false;
	return true;
}

inline bool axisTestZ0(float a, float b, float fa, float fb, Vect3d& v0,
	const Vect3d& v1, const Vect3d& boxhalfsize, float& rad, float& min,
	float& max, float& p0, float& p1) {
	p0 = a * v0.getX() - b * v0.getY();
	p1 = a * v1.getX() - b * v1.getY();
	if (p0 < p1) {
		min = p0;
		max = p1;
	} else {
		min = p1;
		max = p0;
	}
	rad = fa * boxhalfsize.getX() + fb * boxhalfsize.getY();
	if (min > rad || max < -rad)
		return false;
	return true;
}


inline void findMinMax(float x0, float x1, float x2, float& min, float& max) {
	min = max = x0;
	if (x1 < min)
		min = x1;
	if (x1 > max)
		max = x1;
	if (x2 < min)
		min = x2;
	if (x2 > max)
		max = x2;
}


bool AABB::aabbTri(Triangle3d& t) {

	/*    use separating axis theorem to test overlap between triangle and box */

	/*    need to test for overlap in these directions: */

	/*    1) the {x,y,z}-directions (actually, since we use the AABB of the triangle */

	/*       we do not even need to test these) */

	/*    2) normal of the triangle */

	/*    3) crossproduct(edge from tri, {x,y,z}-directin) */

	/*       this gives 3x3=9 more tests */

	Vect3d v0, v1, v2;

	//   float axis[3];

	float min, max, p0, p1, p2, rad, fex, fey, fez;		// -NJMP- "d" local variable removed

	Vect3d normal, e0, e1, e2;
	Vect3d boxhalfsize = getExtent();
	const int X = 0, Y = 1, Z = 2;


	/* This is the fastest branch on Sun */

	/* move everything so that the boxcenter is in (0,0,0) */

	v0 = t[0].sub(this->getCenter());

	v1 = t[1].sub(this->getCenter());

	v2 = t[2].sub(this->getCenter());



	/* compute triangle edges */

	e0 = v1.sub(v0);      /* tri edge 0 */

	e1 = v2.sub(v1);	  /* tri edge 1 */

	e2 = v0.sub(v2);	  /* tri edge 2 */




	/* Bullet 3:  */

	/*  test the 9 tests first (this was faster) */

	fex = fabsf(e0[X]);

	fey = fabsf(e0[Y]);

	fez = fabsf(e0[Z]);

	if (!axisTestX01(e0[Z], e0[Y], fez, fey, v0, v2, boxhalfsize, rad, min, max, p0, p2))
		return false;
	if (!axisTestY02(e0[Z], e0[X], fez, fex, v0, v2, boxhalfsize, rad, min, max, p0, p2))
		return false;
	if (!axisTestZ12(e0[Y], e0[X], fey, fex, v1, v2, boxhalfsize, rad, min, max, p1, p2))
		return false;



	fex = fabsf(e1[X]);

	fey = fabsf(e1[Y]);

	fez = fabsf(e1[Z]);

	if (!axisTestX01(e1[Z], e1[Y], fez, fey, v0, v2, boxhalfsize, rad, min, max, p0, p2))
		return false;
	if (!axisTestY02(e1[Z], e1[X], fez, fex, v0, v2, boxhalfsize, rad, min, max, p0, p2))
		return false;
	if (!axisTestZ0(e1[Y], e1[X], fey, fex, v0, v1, boxhalfsize, rad, min, max, p0, p1))
		return false;



	fex = fabsf(e2[X]);

	fey = fabsf(e2[Y]);

	fez = fabsf(e2[Z]);

	if (!axisTestX2(e2[Z], e2[Y], fez, fey, v0, v1, boxhalfsize, rad, min, max, p0, p1))
		return false;
	if (!axisTestY1(e2[Z], e2[X], fez, fex, v0, v1, boxhalfsize, rad, min, max, p0, p1))
		return false;
	if (!axisTestZ12(e2[Y], e2[X], fey, fex, v1, v2, boxhalfsize, rad, min, max, p1, p2))
		return false;



	/* Bullet 1: */

	/*  first test overlap in the {x,y,z}-directions */

	/*  find min, max of the triangle each direction, and test for overlap in */

	/*  that direction -- this is equivalent to testing a minimal AABB around */

	/*  the triangle against the AABB */



	/* test in X-direction */

	findMinMax(v0[X], v1[X], v2[X], min, max);

	if (min > boxhalfsize[X] || max < -boxhalfsize[X]) return false;



	/* test in Y-direction */

	findMinMax(v0[Y], v1[Y], v2[Y], min, max);

	if (min > boxhalfsize[Y] || max < -boxhalfsize[Y]) return false;



	/* test in Z-direction */

	findMinMax(v0[Z], v1[Z], v2[Z], min, max);

	if (min > boxhalfsize[Z] || max < -boxhalfsize[Z]) return false;



	/* Bullet 2: */

	/*  test if the box intersects the plane of the triangle */

	/*  compute plane equation of triangle: normal*x+d=0 */

	normal = e0.xProduct(e1);

	// -NJMP- (line removed here)

	if (!planeBoxOverlap(normal, v0, boxhalfsize)) return false;	// -NJMP-



	return true;   /* box and triangle overlaps */
}
