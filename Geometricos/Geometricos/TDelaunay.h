#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Projection_traits_xy_3.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include "PointCloud.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Projection_traits_xy_3<K>  Gt;
typedef CGAL::Delaunay_triangulation_2<Gt> Delaunay;
typedef K::Point_3   CGALPoint;

class TDelaunay {
	friend class DrawTDelaunay;
	Delaunay dt;

public:
	TDelaunay(const std::string& path);
	TDelaunay(PointCloud& pointCloud);
};