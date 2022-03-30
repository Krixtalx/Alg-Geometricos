
/*
 * File:   AABB.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:10
 */

#ifndef AABB_H
#define AABB_H

#include "Vect3d.h"

class Triangle3d;

class AABB {

	friend class DrawAABB;
protected:
	Vect3d _min, _max;								// Edge points of the cube.

public:
	/**
	*	@brief Default constructor.
	*/
	AABB();

	/**
	*	@brief Constructor.
	*/
	AABB(Vect3d& min, Vect3d& max);

	/**
	*	@brief Copy constructor,
	*/
	AABB(const AABB& aabb);

	/**
	*	@brief Destructor.
	*/
	virtual ~AABB();




	/**
	*	@brief Returns the central point of the cube.
	*/
	Vect3d getCenter();

	/**
	*	@brief Returns the vector that goes from the center to the maximum point.
	*/
	Vect3d getExtent();

	/**
	*	@brief Returns the lowest corner of the cube.
	*/
	Vect3d getMin() {
		return _min;
	}

	/**
	*	@brief Returns the maximum points of the cube.
	*/
	Vect3d getMax() {
		return _max;
	}

	/**
	*	@brief Assignment operator.
	*/
	AABB& operator=(const AABB& orig);

	/**
	*	@brief Modifies the minimum point.
	*/
	void setMin(Vect3d& min) {
		min = min;
	}

	/**
	*	@brief Modifies the maximum point.
	*/
	void setMax(Vect3d& max) {
		max = max;
	}

	bool aabbTri(Triangle3d& t);
};



#endif /* AABB_H */

