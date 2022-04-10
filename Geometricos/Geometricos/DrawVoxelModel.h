#pragma once
#include "Draw.h"
#include "../Scene.h"
#include "VoxelModel.h"

class DrawVoxelModel : public Draw {

public:

	DrawVoxelModel(VoxelModel& t, type_voxel tipo);

	DrawVoxelModel(const DrawVoxelModel& dt) : Draw(dt) {
	}

	void drawIt();

};