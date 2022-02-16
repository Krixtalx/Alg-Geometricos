
#include "DrawPointCloud.h"


DrawPointCloud::DrawPointCloud(PointCloud& t) : dt(t), Draw() {
	unsigned i = 0;
	for (auto& point : t.getPoints()) {
		_vertices.push_back(glm::vec3(point.getX(), point.getY(), 0));
		_normals.push_back(glm::vec3(0, 0, 1));
		_indices.push_back(i++);
	}

	buildVAO();
}


void DrawPointCloud::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}


void DrawPointCloud::drawIt() {
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::POINT);
	Scene::getInstance()->addModel(this);

}

