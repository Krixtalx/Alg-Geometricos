
#include "Vect3d.h"
#include "DrawRay3d.h"



DrawRay3d::DrawRay3d(Ray3d& t) : dt(t), Draw() {
	Vect3d orig = t.getPoint(0);
	Vect3d dest = t.getPoint(this->MAXVAL_T);
	_vertices.push_back(glm::vec3(orig.getX(), orig.getY(), orig.getZ()));
	_vertices.push_back(glm::vec3(dest.getX(), dest.getY(), dest.getZ()));

	_normals.push_back(glm::vec3(0, 0, 1));
	_normals.push_back(glm::vec3(0, 0, 1));


	_indices.push_back(0);
	_indices.push_back(1);


	buildVAO();

}


void DrawRay3d::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}


void DrawRay3d::drawIt() {
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::LINE);
	Scene::getInstance()->addModel(this);
}


