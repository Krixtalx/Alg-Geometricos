
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "PointCloud.h"
#include <random>
#include <chrono>

PointCloud::PointCloud()
{
}

PointCloud::PointCloud(int size, float max_x, float max_y)
{
	std::default_random_engine generator;
	generator.seed(time(NULL));
	std::uniform_real_distribution<double> generatorX(-max_x, max_x);
	std::uniform_real_distribution<double> generatorY(-max_y, max_y);
	for (size_t i = 0; i < size; i++) {
		_points.emplace_back(Point(generatorX(generator), generatorY(generator)));
	}

}

PointCloud::PointCloud(const std::string& filename)
{
	std::ifstream fin(filename, std::ios::in);
	if (!fin.is_open()) {
		throw std::runtime_error("[PointCloud::PointCloud] -> No se ha podido abrir el filestream para cargar el fichero.");
	}

	std::string line;
	while (std::getline(fin, line)) {
		auto pos = line.find(' ');
		float x = std::stof(line.substr(0, pos));
		float y = std::stof(line.substr(pos));
		_points.emplace_back(x, y);
	}

	fin.close();
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
	std::ofstream fout(filename, std::ios::out);
	if (!fout.is_open()) {
		throw std::runtime_error("[PointCloud::Save] -> No se ha podido abrir el filestream para guardar el fichero.");
	}
	for (auto& point : _points) {
		fout << point.getX() << " " << point.getY() << std::endl;
	}

	fout.close();
}