#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/convex_hull_3.h>
#include "3d/TriangleModel.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Polyhedron_3<K>                     Polyhedron_3;
typedef K::Point_3                                Point_3;
typedef CGAL::Surface_mesh<Point_3>               Surface_mesh;

class ConvexHull3D {
	friend class DrawConvexHull3D;
	Surface_mesh convexHull;

public:
	ConvexHull3D(const std::string& path);
	ConvexHull3D(TriangleModel& triangleModel);
};