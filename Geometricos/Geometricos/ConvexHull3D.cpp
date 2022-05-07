#include "ConvexHull3D.h"

ConvexHull3D::ConvexHull3D(TriangleModel& triangleModel) {
	auto faces(triangleModel.getFaces());
	std::vector<Point_3> points(faces.size() * 3);
	for (auto face : faces) {
		Vect3d v(face.getA());
		Point_3 p(v.getX(), v.getY(), v.getZ());
		points.push_back(p);
		v = face.getB();
		Point_3 p2(v.getX(), v.getY(), v.getZ());
		points.push_back(p2);
		v = face.getC();
		Point_3 p3(v.getX(), v.getY(), v.getZ());
		points.push_back(p3);
	}
	CGAL::convex_hull_3(points.begin(), points.end(), convexHull);
	std::cout << "Num vertices: " << convexHull.number_of_vertices() << std::endl;
}
