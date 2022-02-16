
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "PointCloud.h"
#include <random>


PointCloud::PointCloud()
{
}

PointCloud::PointCloud(int size, float max_x, float max_y)
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> generatorX(-max_x, max_x);
	std::uniform_real_distribution<double> generatorY(-max_y, max_y);
	for (size_t i = 0; i < size; i++) {
		_points.emplace_back(Point(generatorX(generator), generatorY(generator)));
	}

}

PointCloud::PointCloud(const std::string& filename)
{
	//XXXX
}

PointCloud::~PointCloud()
{
}

void PointCloud::addPoint(Point& p)
{
	_points.push_back(p);
}

Point PointCloud::centralPoint()
{
	float currentX = .0f;
	float currentY = .0f;
	for (auto& point : _points) {
		currentX += point.getX();
		currentY += point.getY();
	}
	currentX /= _points.size();
	currentY /= _points.size();
	return Point(currentX, currentY);
}

void PointCloud::deletePoint(int index)
{
	if (index < _points.size()) {
		_points.erase(_points.begin() + index);
	}
}



Point PointCloud::getPoint(int position)
{
	if ((position >= 0) && (position < _points.size())) {
		return _points[position];
	}

	return Point();
}

PointCloud& PointCloud::operator=(const PointCloud& pointCloud)
{
	if (this != &pointCloud) {
		this->_points = pointCloud._points;
	}

	return *this;
}

void PointCloud::save(const std::string& filename)
{
	//XXXX
}