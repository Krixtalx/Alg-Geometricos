#include "Voxel.h"

Voxel::Voxel() : AABB(), processed(false), tipo(type_voxel::none) {
}

Voxel::Voxel(Vect3d& min, Vect3d& max) : AABB(min, max), processed(false), tipo(type_voxel::none) {
}

Voxel::Voxel(const Voxel& other) : tipo(other.tipo), processed(other.processed), AABB(other) {
}

Voxel& Voxel::operator=(const Voxel& other) {
	this->_min = other._min;
	this->_max = other._max;
	this->tipo = other.tipo;
	this->processed = other.processed;
	return *this;
}

void Voxel::setTriangle(int reference) {
	triangleReferences.push_back(reference);
	if (!processed) {
		processed = true;
		tipo = type_voxel::grey;
	}
}

void Voxel::setType(type_voxel type) {
	tipo = type;
	processed = true;
}

void Voxel::setSize(Vect3d& min, Vect3d& max) {
	setMin(min);
	setMax(max);
}

std::vector<int>& Voxel::getReferences() {
	return triangleReferences;
}

bool Voxel::isProcessed() const {
	return processed;
}

type_voxel Voxel::getType() const {
	return tipo;
}
