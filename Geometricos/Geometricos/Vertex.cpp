#include <iostream>
#include <string>
#include "PolygonGeo.h"
#include "Vertex.h"


Vertex::Vertex()
	: Point()
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

Vertex::Vertex(const Point& point)
	: Point(point)
{
	_position = INVALID_POSITION;
	_polygon = nullptr;
}

Vertex::Vertex(const Point& point, PolygonGeo* polygon, int pos)
	: Point(point)
{
	_position = pos;
	_polygon = polygon;
}

Vertex::~Vertex()
{
}

bool Vertex::convex()
{
	//XXXX

	return false;
}

bool Vertex::concave()
{
	//XXXX
	return 0;
}



Vertex Vertex::next()
{
	return _polygon->next(_position);
}

SegmentLine Vertex::nextEdge()
{
	return this->_polygon->getEdge(_position + 1);
}

Vertex& Vertex::operator=(const Vertex& vertex)
{
	if (this != &vertex) {
		Point::operator=(vertex);
		this->_polygon = vertex._polygon;
		this->_position = vertex._position;
	}

	return *this;
}


SegmentLine Vertex::previousEdge()
{
	return this->_polygon->getEdge(_position - 1);
}


void Vertex::out()
{
	Point::out();
	std::cout << "Position: " << std::to_string(_position);
}

Vertex Vertex::previous()
{
	return _polygon->next(_position);
}


