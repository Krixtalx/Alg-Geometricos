#pragma once
#include "3D/AABB.h"

enum class type_voxel {
	white,
	grey,
	black,
	none
};

class Voxel :public AABB {
	bool processed;
	type_voxel tipo;
	std::vector<int> triangleReferences;
public:
	Voxel();
	Voxel(Vect3d& min, Vect3d& max);
	Voxel(const Voxel& other);
	Voxel& operator=(const Voxel& other);

	void setTriangle(int reference);
	void setType(type_voxel type);
	void setSize(Vect3d& min, Vect3d& max);

	bool isProcessed() const;
	type_voxel getType() const;
};