#include <iostream>
#include <cmath>
#include <string>
#include "Vect3d.h"
#include "../BasicGeometry.h"
#include "Triangle3d.h"


Vect3d::Vect3d() {
	this->setVert(DEFAULT_VALUE, DEFAULT_VALUE, DEFAULT_VALUE);
}

Vect3d::Vect3d(double x, double y, double z) {
	this->_value[X] = x;
	this->_value[Y] = y;
	this->_value[Z] = z;
}

Vect3d::Vect3d(const Vect3d& vector) {
	_value[X] = vector._value[X];
	_value[Y] = vector._value[Y];
	_value[Z] = vector._value[Z];
}

Vect3d::~Vect3d() {
}

Vect3d Vect3d::add(const Vect3d& b) const {
	return Vect3d(getX() + b.getX(), getY() + b.getY(), getZ() + b.getZ());
}

bool Vect3d::collinear(Vect3d& a, Vect3d& b) {
	Triangle3d tr(a, b, *this);

	return BasicGeometry::equal(tr.area(), BasicGeometry::EPSILON);
}

double Vect3d::distance(Vect3d& p) {
	return std::sqrt(std::pow(p._value[X] - _value[X], 2) + std::pow(p._value[Y] - _value[Y], 2) + std::pow(p._value[Z] - _value[Z], 2));
}

double Vect3d::dot(const Vect3d& v) {
	return (getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ());
}

std::vector<double> Vect3d::getVert() {
	return std::vector<double> {getX(), getY(), getZ()};
}

double Vect3d::getX() const {
	return _value[X];
}

double Vect3d::getY() const {
	return _value[Y];
}

double Vect3d::getZ() const {
	return _value[Z];
}

double Vect3d::module() {
	return sqrt(_value[X] * _value[X] + _value[Y] * _value[Y] + _value[Z] * _value[Z]);
}

Vect3d& Vect3d::operator=(const Vect3d& vector) {
	this->_value[X] = vector._value[X];
	this->_value[Y] = vector._value[Y];
	this->_value[Z] = vector._value[Z];

	return *this;
}

bool Vect3d::operator==(const Vect3d& vector) {
	return BasicGeometry::equal(getX(), vector._value[X]) && BasicGeometry::equal(getY(), vector._value[Y]) && BasicGeometry::equal(getZ(), vector._value[Z]);
}

bool Vect3d::operator!=(const Vect3d& vector) {
	return !(this->operator==(vector));
}

float Vect3d::operator[](const int& pos) {
	return _value[pos];
}

Vect3d Vect3d::scalarMul(double value) const {
	return Vect3d(getX() * value, getY() * value, getZ() * value);
}

void Vect3d::setX(double x) {
	this->_value[X] = x;
}

void Vect3d::setY(double y) {
	this->_value[Y] = y;
}

void Vect3d::setZ(double z) {
	this->_value[Z] = z;
}

void Vect3d::setVert(double x, double y, double z) {
	this->_value[X] = x;
	this->_value[Y] = y;
	this->_value[Z] = z;
}

Vect3d Vect3d::sub(const Vect3d& b) const {
	return Vect3d(getX() - b.getX(), getY() - b.getY(), getZ() - b.getZ());
}

Vect3d Vect3d::xProduct(const Vect3d& b) const {
	return Vect3d(getY() * b.getZ() - getZ() * b.getY(), getZ() * b.getX() - getX() * b.getZ(), getX() * b.getY() - getY() * b.getX());
}

Vect3d Vect3d::normalize() {
	float mod = this->module();
	return Vect3d(_value[0] / mod, _value[1] / mod, _value[2] / mod);
}

void Vect3d::out() {
	std::cout << "x: " << std::to_string(getX()) << ", y: ";
	std::cout << std::to_string(getY()) << ", z: " << std::to_string(getZ());
}

glm::vec3 Vect3d::toGLM() {
	return glm::vec3(_value[X], _value[Y], _value[Z]);
}
