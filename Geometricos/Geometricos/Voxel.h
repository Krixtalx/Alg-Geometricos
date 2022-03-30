#pragma once
#include "3D/AABB.h"
class Voxel :public AABB {
	enum type_voxel {
		white,
		grey,
		black
	};
	bool processed;
	type_voxel tipo;
};