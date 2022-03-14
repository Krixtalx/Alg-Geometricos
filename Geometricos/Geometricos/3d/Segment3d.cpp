
#include <iostream>
#include "Segment3d.h"


Segment3d::Segment3d(const Vect3d & orig, const Vect3d & dest)
	: Edge3d(orig, dest)
{
}

Segment3d::Segment3d(const Segment3d & segment)
	: Edge3d(segment)
{
}

Segment3d::~Segment3d()
{
}

Segment3d & Segment3d::operator=(const Segment3d & segment)
{
	if (this != &segment)
	{
		Edge3d::operator=(segment);
	}

	return *this;
}

void Segment3d::out()
{
	std::cout << "Segment->Origin: ";
	_orig.out();
	std::cout << "Segment->Destination: ";
	_dest.out();
}