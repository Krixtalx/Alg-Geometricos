#include "VoxelModel.h"
#include <iostream>


VoxelModel::VoxelModel(TriangleModel& tm, int numSubdivs) :deleteTM(false), aabb(tm.getAABB()) {
	this->tm = &tm;
	Vect3d intervals = aabb.getExtent().scalarMul((float)2 / numSubdivs);
	voxelSize = -INFINITY;
	int coord = -1;;
	for (size_t i = 0; i < 3; i++) {
		if (voxelSize < intervals[i]) {
			voxelSize = intervals[i];
			coord = i;
		}
	}
	Vect3d size = aabb.getExtent().scalarMul(2);
	for (size_t i = 0; i < 3; i++) {
		subdivisions[i] = std::ceil(size[i] / intervals[coord]) + 0.5f;
	}

	Vect3d aabbMin(aabb.getMin());
	malla.resize(subdivisions[0]);
	for (size_t x = 0; x < subdivisions[0]; x++) {
		malla[x].resize(subdivisions[1]);
		for (size_t y = 0; y < subdivisions[1]; y++) {
			malla[x][y].resize(subdivisions[2]);
			for (size_t z = 0; z < subdivisions[2]; z++) {
				Vect3d min(aabbMin[0] + voxelSize * x, aabbMin[1] + voxelSize * y, aabbMin[2] + voxelSize * z);
				Vect3d max(aabbMin[0] + voxelSize * (x + 1), aabbMin[1] + voxelSize * (y + 1), aabbMin[2] + voxelSize * (z + 1));
				malla[x][y][z].setSize(min, max);
			}
		}
	}

	computeTriangleModel();
}

VoxelModel::VoxelModel(const std::string& filename, int numSubdivs) : deleteTM(true) {
	tm = new TriangleModel(filename);
	aabb = tm->getAABB();
	Vect3d intervals = aabb.getExtent().scalarMul((float)2 / numSubdivs);
	voxelSize = -INFINITY;
	int coord = -1;;
	for (size_t i = 0; i < 3; i++) {
		if (voxelSize < intervals[i]) {
			voxelSize = intervals[i];
			coord = i;
		}
	}
	Vect3d size = aabb.getExtent().scalarMul(2);
	for (size_t i = 0; i < 3; i++) {
		subdivisions[i] = size[i] / intervals[coord] + 0.5f;
	}

	malla.resize(subdivisions[0]);
	for (size_t x = 0; x < subdivisions[0]; x++) {
		malla[x].resize(subdivisions[1]);
		for (size_t y = 0; y < subdivisions[1]; y++) {
			malla[x][y].resize(subdivisions[2]);
			for (size_t z = 0; z < subdivisions[2]; z++) {
				Vect3d min(voxelSize * x, voxelSize * y, voxelSize * z);
				Vect3d max(voxelSize * (x + 1), voxelSize * (y + 1), voxelSize * (z + 1));
				malla[x][y][z].setSize(min, max);
			}
		}
	}

	computeTriangleModel();
}

/**
 * Calcula de que tipo es cada voxel. Usa OpenMP para paralelizar el proceso (En este proyecto, el perfil Release está configurado para usarlo)
 *
 */
void VoxelModel::computeTriangleModel() {
	auto triangles = tm->getFaces();
	int numVoxelBlancos = 0, numVoxelGrises = 0, numVoxelNegros = 0;
	#pragma omp parallel for
	for (int x = 0; x < subdivisions[0]; x++) {
		for (int y = 0; y < subdivisions[1]; y++) {
			for (int z = 0; z < subdivisions[2]; z++) {
				int index = 0;
				for (auto& triangle : triangles) {
					if (malla[x][y][z].aabbTri(triangle))
						malla[x][y][z].setTriangle(index);
					index++;
				}
				if (!malla[x][y][z].isProcessed()) {
					if (tm->pointIntoMesh(malla[x][y][z].getCenter())) {
						malla[x][y][z].setType(type_voxel::black);
						numVoxelNegros++;
					} else {
						malla[x][y][z].setType(type_voxel::white);
						numVoxelBlancos++;
					}
				} else {
					numVoxelGrises++;
				}
			}
		}
	}
	std::cout << "Num Voxels Blancos: " << numVoxelBlancos << std::endl;
	std::cout << "Num Voxels Grises: " << numVoxelGrises << std::endl;
	std::cout << "Num Voxels Negros: " << numVoxelNegros << std::endl;
	std::cout << "Num total voxels: " << subdivisions[0] * subdivisions[1] * subdivisions[2] << std::endl;
}

/**
 * Comprueba si un punto se encuentra dentro o fuera del modelo asociado a esta malla
 *
 * \param v
 * \return
 */
bool VoxelModel::pointIntoMesh(const Vect3d& v) {
	Vect3d localPos = v.sub(aabb.getMin());
	int x = localPos[0] / voxelSize;
	int y = localPos[1] / voxelSize;
	int z = localPos[2] / voxelSize;

	switch (malla[x][y][z].getType()) {
	case type_voxel::black:
		return true;
		break;
	case type_voxel::white:
		return false;
		break;
	case type_voxel::grey:
		return tm->pointIntoMesh(v);
		break;
	}
}

const std::vector<std::vector<std::vector<Voxel>>>& VoxelModel::getMalla() {
	return malla;
}
