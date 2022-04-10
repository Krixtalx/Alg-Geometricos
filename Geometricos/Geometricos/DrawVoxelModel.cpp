#include "DrawVoxelModel.h"
#include "Voxel.h"

DrawVoxelModel::DrawVoxelModel(VoxelModel& t, type_voxel tipo) {
	auto& malla = t.getMalla();
	int offset = 0;
	std::vector tempNormals({ glm::normalize(glm::vec3(-0.5f, -0.5f, 0.5f)),
								glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),
								glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),
								glm::normalize(glm::vec3(0.5f, -0.5f, -0.5f)),
								glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f)),
								glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
								glm::normalize(glm::vec3(-0.5f, 0.5f, -0.5f)),
								glm::normalize(glm::vec3(0.5f, 0.5f, -0.5f)) });
	std::vector tempIBO({ 0, 1, 2, 0xFFFF, 1, 3, 2, 0xFFFF, 4, 5, 6,
						  5, 7, 6, 0xFFFF, 0, 1, 4, 0xFFFF, 1, 5, 4,
						  2, 0, 4, 0xFFFF, 2, 4, 6, 0xFFFF, 1, 3, 5,
						  3, 7, 5, 0xFFFF, 3, 2, 6, 0xFFFF, 2, 6, 7 });

	for (size_t x = 0; x < malla.size(); x++) {
		for (size_t y = 0; y < malla[x].size(); y++) {
			for (size_t z = 0; z < malla[x][y].size(); z++) {
				if (malla[x][y][z].isProcessed() && malla[x][y][z].getType() == tipo) {
					Vect3d minValues = malla[x][y][z].getMin();
					Vect3d maxValues = malla[x][y][z].getMax();
					offset = _vertices.size();
					_vertices.push_back(glm::vec3(minValues[0], minValues[1], maxValues[2]));
					_vertices.push_back(glm::vec3(maxValues[0], minValues[1], maxValues[2]));
					_vertices.push_back(glm::vec3(minValues[0], minValues[1], minValues[2]));
					_vertices.push_back(glm::vec3(maxValues[0], minValues[1], minValues[2]));
					_vertices.push_back(glm::vec3(minValues[0], maxValues[1], maxValues[2]));
					_vertices.push_back(glm::vec3(maxValues[0], maxValues[1], maxValues[2]));
					_vertices.push_back(glm::vec3(minValues[0], maxValues[1], minValues[2]));
					_vertices.push_back(glm::vec3(maxValues[0], maxValues[1], minValues[2]));

					for (size_t i = 0; i < tempIBO.size(); i++) {
						if (tempIBO[i] != 0xFFFF)
							_indices.push_back(offset + tempIBO[i]);
						else
							_indices.push_back(tempIBO[i]);
					}

					for (size_t i = 0; i < 8; i++) {
						_normals.push_back(tempNormals[i]);
					}
				}
			}
		}
	}
	buildVAO();

	if (tipo == type_voxel::black) {
		setColorActivo(TypeColor{ 0,0,0,1 });
		setAmbient({ 0,0,0,1 });
		//setDiffuse({ 0,0,0,.3 });
	} else if (tipo == type_voxel::grey) {
		setColorActivo(TypeColor{ 0.5,0.5,0.5,.2 });
		setAmbient({ 0.5,0.5,0.5,.2 });
		//setDiffuse({ 0.5,0.5,0.5,.2 });
	} else {
		setColorActivo(TypeColor{ 1,1,1,1 });
		setAmbient({ 1,1,1,1 });
		//setDiffuse({ 1,1,1,.6 });
	}
}

void DrawVoxelModel::drawIt() {
	//Shader custom. Simplemente asigna el color sin usar luces ni texturas.
	setShaderProgram("custom");
	setDrawMode(TypeDraw::CUSTOM);
	Scene::getInstance()->addModel(this);
}
