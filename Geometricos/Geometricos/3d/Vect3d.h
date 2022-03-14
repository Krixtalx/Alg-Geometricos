
/*
 * File:   Vect3d.h
 * Author: lidia
 *
 * Created on 25 de enero de 2021, 19:11
 */

#ifndef VECT3D_H
#define VECT3D_H


#include <limits.h>
#include <vector>

#include <glm/ext/vector_float3.hpp>


class Triangle3d;

/**
*	@brief Base class for any structure which needs 3 coordinates (point, vector...).
*	@author Lidia Mª Ortega Alvarado.
*/
class Vect3d {
protected:
	const static int DEFAULT_VALUE = INT_MAX;	// Value of X and Y coordinates for an incomplete vector.

	enum Axes { X, Y, Z };

private:
	double _value[3];

public:
	/**
	*	@brief Default constructor.
	*/
	Vect3d();

	/**
	*	@brief Constructor.
	*/
	Vect3d(double x, double y, double z);

	/**
	*	@brief Copy constructor.
	*/
	Vect3d(const Vect3d& vector);

	/**
	*	@brief Destructor.
	*/
	virtual ~Vect3d();

	/**
	*	@brief Vector sum. a + b.
	*/
	Vect3d add(const Vect3d& b);

	/**
	*	@brief Checks if a, b and this vector are on a same line.
	*/
	bool collinear(Vect3d& a, Vect3d& b);

	/**
	*	@brief Distance between points.
	*/
	double distance(Vect3d& p);

	/**
	*	@brief Dot product.
	*/
	double dot(const Vect3d& v);

	/**
	*	@brief Returns the coordinates of this vector as an array.
	*/
	std::vector<double> getVert();

	/**
	*	@brief Returns a certain coordinate of the vector.
	*/
	double get(unsigned int index) { return _value[index]; }

	/**
	*	@brief Returns the X coordinate.
	*/
	double getX() const;

	/**
	*	@brief Returns the Y coordinate.
	*/
	double getY() const;

	/**
	*	@brief Returns the Z coordinate.
	*/
	double getZ() const;

	/**
	*	@brief Returns the module of the vector.
	*/
	double module();

	/**
	*	@brief Assignment operator.
	*/
	virtual Vect3d& operator=(const Vect3d& vector);

	/**
	*	@brief Checks if two vectors are equal.
	*/
	virtual bool operator==(const Vect3d& vector);

	/**
	*	@brief Checks if two vectors are distinct.
	*/
	virtual bool operator!=(const Vect3d& vector);

	virtual float operator[](const int& pos);

	/**
	*	@brief Multiplication of this vector by an scalar value.
	*/
	Vect3d scalarMul(double value);

	/**
	*	@brief Modifies the value of a certain coordinate.
	*/
	void set(unsigned int index, double value) { _value[index] = value; }

	/**
	*	@brief Modifies the X coordinate.
	*/
	void setX(double x);

	/**
	*	@brief Modifies the Y coordinate.
	*/
	void setY(double y);

	/**
	*	@brief Modifies the Z coordinate.
	*/
	void setZ(double z);

	/**
	*	@brief Modifies all the vector values.
	*/
	void setVert(double x, double y, double z);

	/**
	*	@brief Vector subtraction.
	*/
	Vect3d sub(const Vect3d& b);

	/**
	*	@brief Vectorial product.
	*/
	Vect3d xProduct(const Vect3d& b);

	/**
	*	@brief Shows some information of the vector at the debug window.
	*/
	virtual void out();

	glm::vec3 toGLM();
};



#endif /* VECT3D_H */

