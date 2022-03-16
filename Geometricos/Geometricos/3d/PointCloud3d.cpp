#include <cmath>
#include <inttypes.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "../BasicGeometry.h"
#include "PointCloud3d.h"
#include <corecrt_math_defines.h>
#include <iostream>


PointCloud3d::PointCloud3d()
	: _maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
}

PointCloud3d::PointCloud3d(std::vector<Vect3d>& pointCloud) : _points(pointCloud),
_maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
}

PointCloud3d::PointCloud3d(const std::string& filename)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
	auto splitByComma = [this](std::string& string) -> std::vector<std::string> {
		std::stringstream ss(string);
		std::vector<std::string> result;

		while (ss.good()) {
			std::string substr;
			getline(ss, substr, ',');
			result.push_back(substr);
		}

		return result;
	};

	std::string currentLine; 				// Línea actual del fichero.
	std::ifstream inputStream;				// Flujo de entrada.
	inputStream.open(filename.c_str());

	while (std::getline(inputStream, currentLine)) {
		std::vector<std::string> coord = splitByComma(currentLine);

		if (coord.size() == 3) {
			try {
				Vect3d point(std::stof(coord[0].c_str(), nullptr), std::stof(coord[1].c_str(), nullptr), (std::stof(coord[2].c_str(), nullptr)));
				this->addPoint(point);
			} catch (const std::exception& excep) {
				inputStream.close();

				throw excep;
			}
		}
	}
	inputStream.close();					// Cerramos fichero.
}

PointCloud3d::PointCloud3d(int size, float max_x, float max_y, float max_z)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
	_points = std::vector<Vect3d>();

	while (size > 0) {
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_x * 2.0f))) - max_x;
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_y * 2.0f))) - max_y;
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_z * 2.0f))) - max_z;
		Vect3d val(x, y, z);
		this->addPoint(val);

		--size;
	}
}

PointCloud3d::PointCloud3d(int size, Vect3d min, Vect3d max) : _maxPoint(max), _minPoint(min) {
	while (size > 0) {
		float x = min.getX() + fmod(rand(), (max.getX() - min.getX()));
		float y = min.getY() + fmod(rand(), (max.getY() - min.getY()));
		float z = min.getZ() + fmod(rand(), (max.getZ() - min.getZ()));
		Vect3d val(x, y, z);
		this->addPoint(val);

		--size;
	}
}

PointCloud3d::PointCloud3d(int size, float radius)
	: _maxPoint(-INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
	_points = std::vector<Vect3d>();

	while (size > 0) {
		float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)) * 2.0f * M_PI;
		float phi = std::acos(1.0f - 2.0f * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
		double x = std::sin(phi) * std::cos(theta);
		double y = std::sin(phi) * std::sin(theta);
		double z = std::cos(phi);

		float r = radius * std::sqrt(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX)));
		Vect3d point(r * x, r * y, r * z);
		this->addPoint(point);

		--size;
	}
}

PointCloud3d::PointCloud3d(const PointCloud3d& pointCloud)
	: _points(pointCloud._points), _maxPoint(pointCloud._maxPoint), _minPoint(pointCloud._minPoint) {
}

PointCloud3d::~PointCloud3d() {

}

void PointCloud3d::addPoint(Vect3d& p) {
	_points.push_back(p);
	this->updateMaxMin(_points.size() - 1);
}

AABB PointCloud3d::getAABB() {
	return AABB(_minPoint, _maxPoint);
}



Vect3d PointCloud3d::getPoint(int pos) {
	if ((pos >= 0) && (pos < _points.size())) {
		return _points[pos];
	}
	return Vect3d();
}

PointCloud3d& PointCloud3d::operator=(const PointCloud3d& pointCloud) {
	if (this != &pointCloud) {
		_points = pointCloud._points;
		_maxPoint = pointCloud._maxPoint;
		_minPoint = pointCloud._minPoint;
	}

	return *this;
}

void PointCloud3d::save(const std::string& filename) {
	std::ofstream file(filename);

	for (int i = 0; i < _points.size(); ++i) {
		file << _points[i].getX() << ", " << _points[i].getY() << ", " << _points[i].getZ() << std::endl;
	}

	file.close();
}


/// PROTECTED METHODS

void PointCloud3d::updateMaxMin(int index) {
	Vect3d point = _points[index];

	if (point.getX() < _minPoint.getX()) { _minPoint.setX(point.getX()); _minPointIndex.setX(index); }
	if (point.getY() < _minPoint.getY()) { _minPoint.setY(point.getY()); _minPointIndex.setY(index); }
	if (point.getZ() < _minPoint.getZ()) { _minPoint.setZ(point.getZ()); _minPointIndex.setZ(index); }

	if (point.getX() > _maxPoint.getX()) { _maxPoint.setX(point.getX()); _maxPointIndex.setX(index); }
	if (point.getY() > _maxPoint.getY()) { _maxPoint.setY(point.getY()); _maxPointIndex.setY(index); }
	if (point.getZ() > _maxPoint.getZ()) { _maxPoint.setZ(point.getZ()); _maxPointIndex.setZ(index); }
}


void PointCloud3d::getMostDistanced(int& a, int& b) {
	a = -1; b = -1;
	float currentMaxDistance = -FLT_MAX;
	float dist = 0;
	for (size_t i = 0; i < _points.size(); i++) {
		for (size_t j = i + 1; j < _points.size(); j++) {
			dist = _points[i].distance(_points[j]);
			if (dist > currentMaxDistance) {
				a = i; b = j;
				currentMaxDistance = dist;
			}
		}
	}
}
