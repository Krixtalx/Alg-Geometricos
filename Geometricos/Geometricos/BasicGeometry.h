#pragma once

#include <cfloat>
#include "3d/Vect3d.h"

namespace BasicGeometry {
	const double EPSILON = 0.00001;			// Avoids problems with the resolution.
	const double ZERO = 0.000000f;
	const double INFINITO = DBL_MAX;

	/**
	*	@brief Checks if two values are equal.
	*/
	bool equal(double a, double b);

	/**
	*	@brief Determinant 2x2.
	*/
	double determinant2x2(double a, double b, double c, double d);


	double determinant3x3(Vect3d a, Vect3d b, Vect3d c);

	/**
	*	@brief Determinant 3x3.
	*/
	double determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i);

	/**
	*	@brief Returns the mininum value from the 3 specified values.
	*/
	double min3(double a, double b, double c);

	/**
	*	@brief Returns the maximum value from the 3 specified values.
	*/
	double max3(double a, double b, double c);

	/**
*	@brief Returns the mininum value from the 2 specified values.
*/
	double min2(double a, double b);

	/**
	*	@brief Returns the maximum value from the 2 specified values.
	*/
	double max2(double a, double b);

	/**
	*  @brief Returns if any of the vector's value is the same as the corresponding one in the other vector
	*/
	bool anyEqual(const Vect3d& a, const Vect3d& b);

};

inline bool BasicGeometry::equal(double a, double b) {
	return (abs(a - b) < EPSILON);
}

inline double BasicGeometry::determinant2x2(double a, double b, double c, double d) {
	return (a * c - b * d);
}

inline double BasicGeometry::determinant3x3(Vect3d a, Vect3d b, Vect3d c) {
	return BasicGeometry::determinant3x3(a.getX(), b.getX(), c.getX(), a.getY(), b.getY(), c.getY(), a.getZ(), b.getZ(), c.getZ());
}

inline double BasicGeometry::determinant3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
	return (a * e * i + g * b * f + c * d * h - c * e * g - i * d * b - a * h * f);
}

inline double BasicGeometry::min3(double a, double b, double c) {
	return (a < b ? (a < c ? a : c) : (b < c ? b : c));
}

inline double BasicGeometry::max3(double a, double b, double c) {
	return (a > b ? (a > c ? a : c) : (b > c ? b : c));
}

inline double BasicGeometry::min2(double a, double b) {
	return (a < b ? a : b);
}

inline double BasicGeometry::max2(double a, double b) {
	return (a > b ? a : b);
}

inline bool BasicGeometry::anyEqual(const Vect3d& a, const Vect3d& b) {
	return BasicGeometry::equal(a.getX(), b.getX()) || BasicGeometry::equal(a.getY(), b.getY()) || BasicGeometry::equal(a.getZ(), b.getZ());
}
