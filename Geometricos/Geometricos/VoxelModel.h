#pragma once

#include <vector>
#include "Voxel.h"
#include "3d/TriangleModel.h"

class VoxelModel {
	std::vector<std::vector<std::vector<Voxel>>> malla;
	AABB aabb;
	TriangleModel* tm;
	int subdivisions[3];
	float voxelSize;
	bool deleteTM;

	void computeTriangleModel();

public:
	VoxelModel(TriangleModel& tm, int numSubdivs);
	VoxelModel(const std::string& filename, int numSubdivs);

	bool pointIntoMesh(const Vect3d& v);

	const std::vector<std::vector<std::vector<Voxel>>>& getMalla();
};