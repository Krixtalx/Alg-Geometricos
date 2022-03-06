
#include <iostream>
#include "Edge3d.h"
#include "Ray3d.h"


Ray3d::Ray3d(Vect3d & orig, Vect3d & dest)
	: Edge3d(orig, dest)
{
}

Ray3d::Ray3d(const Ray3d & ray)
	: Edge3d(ray)
{
}

Ray3d::~Ray3d()
{
}

Ray3d & Ray3d::operator=(const Ray3d & ray)
{
	if (this != &ray)
	{
		Edge3d::operator=(ray);
	}

	return *this;
}

void Ray3d::out()
{
	std::cout << "Ray->Origin: ";
	_orig.out();
	std::cout << "Ray->Destination: ";
	_dest.out();
}