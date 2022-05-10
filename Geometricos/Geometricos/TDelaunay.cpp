#include "TDelaunay.h"

TDelaunay::TDelaunay(const std::string& path) {
	PointCloud pointCloud(path);
	auto points(pointCloud.getPoints());
	for (auto point : points) {
		CGALPoint p(point.getX(), point.getY(), 0);
		dt.insert(p);
	}
	std::cout << "Num vertices: " << dt.number_of_vertices() << std::endl;
}

TDelaunay::TDelaunay(PointCloud& pointCloud) {
	auto points(pointCloud.getPoints());
	for (auto point : points) {
		CGALPoint p(point.getX(), point.getY(), 0);
		dt.insert(p);
	}
	std::cout << "Num vertices: " << dt.number_of_vertices() << std::endl;
}
