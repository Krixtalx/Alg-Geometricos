#include <iostream>
#include "limits.h"
#include <cmath>
#include "../BasicGeometry.h"
#include "Line3d.h"

Line3d::Line3d() {
}

Line3d::Line3d(const Vect3d& orig, const Vect3d& dest)
	: Edge3d(orig, dest) {
}

Line3d::Line3d(const Line3d& line)
	: Edge3d(line) {
}

Line3d::~Line3d() {
}


double Line3d::distance(Line3d& line) {
	Vect3d qSub = this->_orig.sub(line._orig);
	Vect3d v = this->_dest.sub(this->_orig);
	Vect3d v2 = line._dest.sub(line._orig);
	Vect3d crossV = v.xProduct(v2);

	return std::abs(qSub.dot(crossV)) / crossV.module();
}

Line3d Line3d::normalLine(Vect3d& point) {
	Vect3d pMinusT(point.sub(_orig));
	Vect3d v = this->_dest.sub(this->_orig);
	float lamda = v.dot(pMinusT) / v.dot(v);
	Vect3d vLamda(v.scalarMul(lamda));
	Vect3d tPlusVLamda(_orig.add(vLamda));
	Vect3d normal = point.sub(tPlusVLamda);
	Vect3d newOrig = getPoint(lamda);
	return Line3d(newOrig, point);
}

double Line3d::distance(Vect3d& p) {
	Vect3d pMinusT(p.sub(_orig));
	Vect3d v = this->_dest.sub(this->_orig);
	float lamda = v.dot(pMinusT) / v.dot(v);
	Vect3d vLamda(v.scalarMul(lamda));
	return pMinusT.sub(vLamda).module();
}

Line3d& Line3d::operator=(const Line3d& line) {
	if (this != &line) {
		Edge3d::operator=(line);
	}

	return *this;
}

void Line3d::out() {
	std::cout << "Line->Origin: ";
	_orig.out();
	std::cout << "Line->Destination: ";
	_dest.out();
}

