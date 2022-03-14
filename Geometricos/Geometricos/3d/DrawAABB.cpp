#include "DrawAABB.h"
#include "DrawSegment3d.h"


DrawAABB::DrawAABB(AABB& t) : _aabb(t), Draw() {
	Vect3d minValues = t._min;
	Vect3d maxValues = t._max;

	_vertices.push_back(glm::vec3(minValues[0], minValues[1], maxValues[2]));
	_vertices.push_back(glm::vec3(maxValues[0], minValues[1], maxValues[2]));
	_vertices.push_back(glm::vec3(minValues[0], minValues[1], minValues[2]));
	_vertices.push_back(glm::vec3(maxValues[0], minValues[1], minValues[2]));
	_vertices.push_back(glm::vec3(minValues[0], maxValues[1], maxValues[2]));
	_vertices.push_back(glm::vec3(maxValues[0], maxValues[1], maxValues[2]));
	_vertices.push_back(glm::vec3(minValues[0], maxValues[1], minValues[2]));
	_vertices.push_back(glm::vec3(maxValues[0], maxValues[1], minValues[2]));

	_indices = { 0, 1, 0xFFFF, 0, 2, 0xFFFF,
				 1, 3, 0xFFFF, 2, 3, 0xFFFF,
				 4, 5, 0xFFFF, 4, 6, 0xFFFF,
				 5, 7, 0xFFFF, 6, 7, 0xFFFF,
				 0, 4, 0xFFFF, 1, 5, 0xFFFF,
				 2, 6, 0xFFFF, 3, 7, 0xFFFF };
	_normals = {
			glm::normalize(glm::vec3(-0.5f, -0.5f, 0.5f)),
			glm::normalize(glm::vec3(0.5f, -0.5f, 0.5f)),
			glm::normalize(glm::vec3(-0.5f, -0.5f, -0.5f)),
			glm::normalize(glm::vec3(0.5f, -0.5f, -0.5f)),
			glm::normalize(glm::vec3(-0.5f, 0.5f, 0.5f)),
			glm::normalize(glm::vec3(0.5f, 0.5f, 0.5f)),
			glm::normalize(glm::vec3(-0.5f, 0.5f, -0.5f)),
			glm::normalize(glm::vec3(0.5f, 0.5f, -0.5f)) };
	buildVAO();

}


void DrawAABB::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}


void DrawAABB::drawIt() {

	setShaderProgram("algeom");
	setDrawMode(TypeDraw::LINE);
	Scene::getInstance()->addModel(this);

	//    for (int i=0; i<dsegment.size(); i++)
	//        dsegment[i].drawIt();

}

