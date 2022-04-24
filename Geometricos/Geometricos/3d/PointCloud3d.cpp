#include <cmath>
#include <inttypes.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "../BasicGeometry.h"
#include "PointCloud3d.h"
#include <corecrt_math_defines.h>
#include <iostream>
#include "../Draw.h"
#include "DrawCloud3d.h"
#include "../Voxel.h"


PointCloud3d::PointCloud3d()
	: _maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
}

PointCloud3d::PointCloud3d(std::vector<Vect3d>& pointCloud) : _points(pointCloud),
_maxPoint(INFINITY, -INFINITY, -INFINITY), _minPoint(INFINITY, INFINITY, INFINITY) {
	for (size_t i = 0; i < _points.size(); i++) {
		updateMaxMin(i);
	}
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
	for (size_t i = 0; i < _points.size(); i++) {
		updateMaxMin(i);
	}
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
	for (size_t i = 0; i < size; i++) {
		updateMaxMin(i);
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
	for (size_t i = 0; i < size; i++) {
		updateMaxMin(i);
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

	if (point.getX() < _minPoint.getX()) {
		_minPoint.setX(point.getX()); _minPointIndex.setX(index);
	}
	if (point.getY() < _minPoint.getY()) {
		_minPoint.setY(point.getY()); _minPointIndex.setY(index);
	}
	if (point.getZ() < _minPoint.getZ()) {
		_minPoint.setZ(point.getZ()); _minPointIndex.setZ(index);
	}

	if (point.getX() > _maxPoint.getX()) {
		_maxPoint.setX(point.getX()); _maxPointIndex.setX(index);
	}
	if (point.getY() > _maxPoint.getY()) {
		_maxPoint.setY(point.getY()); _maxPointIndex.setY(index);
	}
	if (point.getZ() > _maxPoint.getZ()) {
		_maxPoint.setZ(point.getZ()); _maxPointIndex.setZ(index);
	}
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

std::vector<std::vector<Vect3d>> PointCloud3d::kmeans_naive(const int k, const int maxIterations) {
	std::vector<std::vector<Vect3d>> result(k);
	std::vector<std::vector<float>> distances(k);
	std::vector<float> meanDistances(k);
	std::vector<Vect3d> centroids(k);
	const int nAux = _points.size() / k;
	const int pointsNumber = _points.size();
	for (int i = 0; i < k; i++) {
		centroids[i] = _points[i * nAux];
	}
	float sumSquareError = INFINITY;
	float prevSumSquareError = 0;
	int currentIt = 0;
	while (!BasicGeometry::equal(sumSquareError, prevSumSquareError) && currentIt < maxIterations) {
		currentIt++;
		prevSumSquareError = sumSquareError;
		for (int i = 0; i < k; i++) {
			result[i].clear();
			distances[i].clear();
			meanDistances[i] = .0f;
		}
#pragma omp parallel for
		for (int i = 0; i < pointsNumber; i++) {
			float minDistance = INFINITY;
			int clusterIndex = -1;
			for (int j = 0; j < k; j++) {
				float distance = _points[i].squareDistance(centroids[j]);
				if (distance < minDistance) {
					minDistance = distance;
					clusterIndex = j;
				}
			}
#pragma omp critical
			result[clusterIndex].push_back(_points[i]);
#pragma omp critical
			distances[clusterIndex].push_back(minDistance);
#pragma omp critical
			meanDistances[clusterIndex] += minDistance;

		}
		sumSquareError = .0f;
		for (int i = 0; i < k; i++) {
			int clusterSize = result[i].size();
			meanDistances[i] /= (float)clusterSize;

			Vect3d newCentroid;
			for (int j = 0; j < clusterSize; j++) {
				newCentroid = newCentroid.add(result[i][j]);
				sumSquareError += pow((distances[i][j] - meanDistances[i]), 2);
			}
			newCentroid = newCentroid.scalarMul(1 / (float)clusterSize);
			centroids[i] = newCentroid;
			//std::cout << "Cluster " + std::to_string(i) + ": " << clusterSize << std::endl;
		}

		sumSquareError /= (float)k;
		//std::cout << "Sum of Squares error: " << std::to_string(sumSquareError) << std::endl;
	}
	std::cout << "Clustering naive finalizado en " << currentIt << " iteraciones." << std::endl;
	return result;
}

void PointCloud3d::kmeans_naive_auto_update(const int k, const int maxIterations, GLFWwindow* ventana) {
	std::vector<std::vector<Vect3d>> result(k);
	std::vector<std::vector<float>> distances(k);
	std::vector<float> meanDistances(k);
	std::vector<Vect3d> centroids(k);
	DrawCloud3d* drawCloud;
	const int nAux = _points.size() / k;
	const int pointsNumber = _points.size();
	for (int i = 0; i < k; i++) {
		centroids[i] = _points[i * nAux];
	}
	float sumSquareError = INFINITY;
	float prevSumSquareError = 0;
	int currentIt = 0;
	while (!BasicGeometry::equal(sumSquareError, prevSumSquareError) && currentIt < maxIterations) {
		currentIt++;
		prevSumSquareError = sumSquareError;
		for (int i = 0; i < k; i++) {
			result[i].clear();
			distances[i].clear();
			meanDistances[i] = .0f;
		}
#pragma omp parallel for
		for (int i = 0; i < pointsNumber; i++) {
			float minDistance = INFINITY;
			int clusterIndex = -1;
			for (int j = 0; j < k; j++) {
				float distance = _points[i].squareDistance(centroids[j]);
				if (distance < minDistance) {
					minDistance = distance;
					clusterIndex = j;
				}
			}
#pragma omp critical
			result[clusterIndex].push_back(_points[i]);
#pragma omp critical
			distances[clusterIndex].push_back(minDistance);
#pragma omp critical
			meanDistances[clusterIndex] += minDistance;

		}
		sumSquareError = .0f;
		for (int i = 0; i < k; i++) {
			int clusterSize = result[i].size();
			meanDistances[i] /= (float)clusterSize;

			Vect3d newCentroid;
			for (int j = 0; j < clusterSize; j++) {
				newCentroid = newCentroid.add(result[i][j]);
				sumSquareError += pow((distances[i][j] - meanDistances[i]), 2);
			}
			newCentroid = newCentroid.scalarMul(1 / (float)clusterSize);
			centroids[i] = newCentroid;
			//std::cout << "Cluster " + std::to_string(i) + ": " << clusterSize << std::endl;
		}

		sumSquareError /= (float)k;
		//std::cout << "Sum of Squares error: " << std::to_string(sumSquareError) << std::endl;

		int id = 0;
		Scene::getInstance()->clearScene();
		for (auto& cluster : result) {
			PointCloud3d cloud(cluster);
			drawCloud = new DrawCloud3d(cloud);
			drawCloud->drawIt(PointCloud3d::getClusterColor(id, k));
			id++;
		}
		Scene::getInstance()->refresh();
		glfwSwapBuffers(ventana);
	}
	std::cout << "Clustering naive finalizado en " << currentIt << " iteraciones." << std::endl;
}

bool compareFunction(std::pair<int, BasicGeometry::int3> left, std::pair<int, BasicGeometry::int3> right) {
	return left.first > right.first;
}

std::vector<std::vector<Vect3d>> PointCloud3d::kmeans_grid(const int k, const int maxIterations, const int subdivisions) {
	std::vector<std::vector<Vect3d>> result(k);
	std::vector<std::vector<float>> distances(k);
	std::vector<float> meanDistances(k);
	std::vector<Vect3d> centroids(k);
	std::vector<std::vector<std::vector<Voxel>>> malla(subdivisions);
	DrawCloud3d* drawCloud;
	const int pointsNumber = _points.size();
	AABB aabb(_minPoint, _maxPoint);
	Vect3d voxelSize = aabb.getExtent().scalarMul((float)2 / subdivisions);
	Vect3d aabbMin(_minPoint);
	std::vector<std::pair<int, BasicGeometry::int3>> centroidsCandidates;
	for (size_t x = 0; x < subdivisions; x++) {
		malla[x].resize(subdivisions);
		for (size_t y = 0; y < subdivisions; y++) {
			malla[x][y].resize(subdivisions);
			for (size_t z = 0; z < subdivisions; z++) {
				Vect3d min(aabbMin[0] + voxelSize[0] * x, aabbMin[1] + voxelSize[1] * y, aabbMin[2] + voxelSize[2] * z);
				Vect3d max(aabbMin[0] + voxelSize[0] * (x + 1), aabbMin[1] + voxelSize[1] * (y + 1), aabbMin[2] + voxelSize[2] * (z + 1));
				malla[x][y][z].setSize(min, max);
			}
		}
	}
#pragma omp parallel for
	for (int i = 0; i < pointsNumber; i++) {
		Vect3d normalized = _points[i].sub(aabbMin);
		int x = normalized[0] / voxelSize[0];
		int y = normalized[1] / voxelSize[1];
		int z = normalized[2] / voxelSize[2];
		if (x < 0)
			x = 0;
		else if (x >= subdivisions)
			x = subdivisions - 1;
		if (y < 0)
			y = 0;
		else if (y >= subdivisions)
			y = subdivisions - 1;
		if (z < 0)
			z = 0;
		else if (z >= subdivisions)
			z = subdivisions - 1;
#pragma omp critical
		malla[x][y][z].setTriangle(i);
	}
#pragma omp parallel for
	for (int x = 0; x < subdivisions; x++) {
		for (int y = 0; y < subdivisions; y++) {
			for (int z = 0; z < subdivisions; z++) {
				int num = 0;
				/*for (int subX = x - 1; subX < x + 2; subX++) {
					for (int subY = y - 1; subY < y + 2; subY++) {
						for (int subZ = z - 1; subZ < z + 2; subZ++) {
							if (!(subX < 0 || subY < 0 || subZ < 0 || subX >= subdivisions || subY >= subdivisions || subZ >= subdivisions)) {
								auto& references = malla[subX][subY][subZ].getReferences();
								num += references.size();
							}
						}
					}
				}*/
				auto& references = malla[x][y][z].getReferences();
				num += references.size();
#pragma omp critical
				centroidsCandidates.push_back(std::make_pair(num, BasicGeometry::int3{ x,y,z }));
			}
		}
	}
	std::sort(centroidsCandidates.begin(), centroidsCandidates.end(), compareFunction);
	for (int i = 0; i < k; i++) {
		BasicGeometry::int3 pos(centroidsCandidates[i].second);
		centroids[i] = malla[pos.x][pos.y][pos.z].getCenter();
	}
	float sumSquareError = INFINITY;
	float prevSumSquareError = 0;
	int currentIt = 0;
	std::vector < std::vector<float>> distanceToGrid(k);
	for (int i = 0; i < k; i++) {
		distanceToGrid[i].resize(subdivisions * subdivisions * subdivisions);
	}
	while (!BasicGeometry::equal(sumSquareError, prevSumSquareError) && currentIt < maxIterations) {
		currentIt++;
		prevSumSquareError = sumSquareError;
#pragma omp parallel for
		for (int i = 0; i < k; i++) {
			result[i].clear();
			distances[i].clear();
			meanDistances[i] = .0f;
			for (int x = 0; x < subdivisions; x++) {
				for (int y = 0; y < subdivisions; y++) {
					for (int z = 0; z < subdivisions; z++) {
						distanceToGrid[i][x * subdivisions * subdivisions + y * subdivisions + z] = centroids[i].squareDistance(malla[x][y][z].getCenter());
					}
				}
			}
		}

#pragma omp parallel for
		for (int i = 0; i < pointsNumber; i++) {
			Vect3d normalized = _points[i].sub(aabbMin);
			int x = normalized[0] / voxelSize[0];
			int y = normalized[1] / voxelSize[1];
			int z = normalized[2] / voxelSize[2];
			float minDistance = INFINITY;
			int clusterIndex = -1;
			for (int j = 0; j < k; j++) {
				float distance = distanceToGrid[j][x * subdivisions * subdivisions + y * subdivisions + z];
				if (distance < minDistance) {
					minDistance = distance;
					clusterIndex = j;
				} else if (BasicGeometry::equal(distance, minDistance)) {
					distance = _points[i].squareDistance(centroids[j]);
					float distance2 = _points[i].squareDistance(centroids[clusterIndex]);
					if (distance < distance2) {
						minDistance = distance;
						clusterIndex = j;
					}
				}
			}
#pragma omp critical
			result[clusterIndex].push_back(_points[i]);
#pragma omp critical
			distances[clusterIndex].push_back(minDistance);
#pragma omp critical
			meanDistances[clusterIndex] += minDistance;

		}
		sumSquareError = .0f;
		for (int i = 0; i < k; i++) {
			int clusterSize = result[i].size();
			meanDistances[i] /= (float)clusterSize;

			Vect3d newCentroid;
			for (int j = 0; j < clusterSize; j++) {
				newCentroid = newCentroid.add(result[i][j]);
				sumSquareError += pow((distances[i][j] - meanDistances[i]), 2);
			}
			newCentroid = newCentroid.scalarMul(1 / (float)clusterSize);
			centroids[i] = newCentroid;
			//std::cout << "Cluster " + std::to_string(i) + ": " << clusterSize << std::endl;
		}

		sumSquareError /= (float)k;
		//std::cout << "Sum of Squares error: " << std::to_string(sumSquareError) << std::endl;
	}
	std::cout << "Clustering grid finalizado en " << currentIt << " iteraciones." << std::endl;
	return result;
}

void PointCloud3d::kmeans_grid_auto_update(const int k, const int maxIterations, const int subdivisions, GLFWwindow* ventana) {
	std::vector<std::vector<Vect3d>> result(k);
	std::vector<std::vector<float>> distances(k);
	std::vector<float> meanDistances(k);
	std::vector<Vect3d> centroids(k);
	std::vector<std::vector<std::vector<Voxel>>> malla(subdivisions);
	DrawCloud3d* drawCloud;
	const int pointsNumber = _points.size();
	AABB aabb(_minPoint, _maxPoint);
	Vect3d voxelSize = aabb.getExtent().scalarMul((float)2 / subdivisions);
	Vect3d aabbMin(_minPoint);
	std::vector<std::pair<int, BasicGeometry::int3>> centroidsCandidates;
	for (size_t x = 0; x < subdivisions; x++) {
		malla[x].resize(subdivisions);
		for (size_t y = 0; y < subdivisions; y++) {
			malla[x][y].resize(subdivisions);
			for (size_t z = 0; z < subdivisions; z++) {
				Vect3d min(aabbMin[0] + voxelSize[0] * x, aabbMin[1] + voxelSize[1] * y, aabbMin[2] + voxelSize[2] * z);
				Vect3d max(aabbMin[0] + voxelSize[0] * (x + 1), aabbMin[1] + voxelSize[1] * (y + 1), aabbMin[2] + voxelSize[2] * (z + 1));
				malla[x][y][z].setSize(min, max);
			}
		}
	}
#pragma omp parallel for
	for (int i = 0; i < pointsNumber; i++) {
		Vect3d normalized = _points[i].sub(aabbMin);
		int x = normalized[0] / voxelSize[0];
		int y = normalized[1] / voxelSize[1];
		int z = normalized[2] / voxelSize[2];
		if (x < 0)
			x = 0;
		else if (x >= subdivisions)
			x = subdivisions - 1;
		if (y < 0)
			y = 0;
		else if (y >= subdivisions)
			y = subdivisions - 1;
		if (z < 0)
			z = 0;
		else if (z >= subdivisions)
			z = subdivisions - 1;
#pragma omp critical
		malla[x][y][z].setTriangle(i);
	}
#pragma omp parallel for
	for (int x = 0; x < subdivisions; x++) {
		for (int y = 0; y < subdivisions; y++) {
			for (int z = 0; z < subdivisions; z++) {
				int num = 0;
				/*for (int subX = x - 1; subX < x + 2; subX++) {
					for (int subY = y - 1; subY < y + 2; subY++) {
						for (int subZ = z - 1; subZ < z + 2; subZ++) {
							if (!(subX < 0 || subY < 0 || subZ < 0 || subX >= subdivisions || subY >= subdivisions || subZ >= subdivisions)) {
								auto& references = malla[subX][subY][subZ].getReferences();
								num += references.size();
							}
						}
					}
				}*/
				auto& references = malla[x][y][z].getReferences();
				num += references.size();
#pragma omp critical
				centroidsCandidates.push_back(std::make_pair(num, BasicGeometry::int3{ x,y,z }));
			}
		}
	}
	std::sort(centroidsCandidates.begin(), centroidsCandidates.end(), compareFunction);
	for (int i = 0; i < k; i++) {
		BasicGeometry::int3 pos(centroidsCandidates[i].second);
		centroids[i] = malla[pos.x][pos.y][pos.z].getCenter();
	}
	float sumSquareError = INFINITY;
	float prevSumSquareError = 0;
	int currentIt = 0;
	std::vector < std::vector<float>> distanceToGrid(k);
	for (int i = 0; i < k; i++) {
		distanceToGrid[i].resize(subdivisions * subdivisions * subdivisions);
	}
	while (!BasicGeometry::equal(sumSquareError, prevSumSquareError) && currentIt < maxIterations) {
		currentIt++;
		prevSumSquareError = sumSquareError;
#pragma omp parallel for
		for (int i = 0; i < k; i++) {
			result[i].clear();
			distances[i].clear();
			meanDistances[i] = .0f;
			for (int x = 0; x < subdivisions; x++) {
				for (int y = 0; y < subdivisions; y++) {
					for (int z = 0; z < subdivisions; z++) {
						distanceToGrid[i][x * subdivisions * subdivisions + y * subdivisions + z] = centroids[i].squareDistance(malla[x][y][z].getCenter());
					}
				}
			}
		}

#pragma omp parallel for
		for (int i = 0; i < pointsNumber; i++) {
			Vect3d normalized = _points[i].sub(aabbMin);
			int x = normalized[0] / voxelSize[0];
			int y = normalized[1] / voxelSize[1];
			int z = normalized[2] / voxelSize[2];
			float minDistance = INFINITY;
			int clusterIndex = -1;
			for (int j = 0; j < k; j++) {
				float distance = distanceToGrid[j][x * subdivisions * subdivisions + y * subdivisions + z];
				if (distance < minDistance) {
					minDistance = distance;
					clusterIndex = j;
				} else if (BasicGeometry::equal(distance, minDistance)) {
					distance = _points[i].squareDistance(centroids[j]);
					float distance2 = _points[i].squareDistance(centroids[clusterIndex]);
					if (distance < distance2) {
						minDistance = distance;
						clusterIndex = j;
					}
				}
			}
#pragma omp critical
			result[clusterIndex].push_back(_points[i]);
#pragma omp critical
			distances[clusterIndex].push_back(minDistance);
#pragma omp critical
			meanDistances[clusterIndex] += minDistance;

		}
		sumSquareError = .0f;
		for (int i = 0; i < k; i++) {
			int clusterSize = result[i].size();
			meanDistances[i] /= (float)clusterSize;

			Vect3d newCentroid;
			for (int j = 0; j < clusterSize; j++) {
				newCentroid = newCentroid.add(result[i][j]);
				sumSquareError += pow((distances[i][j] - meanDistances[i]), 2);
			}
			newCentroid = newCentroid.scalarMul(1 / (float)clusterSize);
			centroids[i] = newCentroid;
			//std::cout << "Cluster " + std::to_string(i) + ": " << clusterSize << std::endl;
		}

		sumSquareError /= (float)k;
		//std::cout << "Sum of Squares error: " << std::to_string(sumSquareError) << std::endl;

		int id = 0;
		Scene::getInstance()->clearScene();
		for (auto& cluster : result) {
			PointCloud3d cloud(cluster);
			drawCloud = new DrawCloud3d(cloud);
			drawCloud->drawIt(PointCloud3d::getClusterColor(id, k));
			id++;
		}
		Scene::getInstance()->refresh();
		glfwSwapBuffers(ventana);
	}
	std::cout << "Clustering grid finalizado en " << currentIt << " iteraciones." << std::endl;
}

TypeColor PointCloud3d::getClusterColor(int index, int k) {
	float increment = 1;
	if (k > 7)
		increment = (float)7 / k;
	float r, g, b, offset, mod;
	r = 0, g = 0, b = 0;
	offset = increment * index;
	if (offset <= 1.0f) {
		r = offset;
	} else if (offset <= 2.0f) {
		g = offset - 1.0f;
	} else if (offset <= 3.0f) {
		b = offset - 2.0f;
	} else if (offset <= 4.0f) {
		r = 1;
		b = offset - 3.0f;
	} else if (offset <= 5.0f) {
		b = 1;
		g = offset - 4.0f;
	} else if (offset <= 6.0f) {
		r = 1;
		g = offset - 5.0f;
	} else if (offset <= 7.0f) {
		r = 1;
		b = 1;
		g = offset - 6.0f;
	}

	//std::cout << "Color " + std::to_string(index) + ": " << std::to_string(r) + " - " << std::to_string(g) + " - " << std::to_string(b) + " - " << std::endl;
	return TypeColor(r, g, b, 1);
}
