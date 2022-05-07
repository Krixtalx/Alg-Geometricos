#include "DrawConvexHull3D.h"
#include "Scene.h"

DrawConvexHull3D::DrawConvexHull3D(const ConvexHull3D& ch) {
	_vertices.resize(ch.convexHull.number_of_vertices());
	for (auto& vertIdx : ch.convexHull.vertices()) {
		glm::vec3 v;
		auto vert = ch.convexHull.point(vertIdx);
		v.x = vert.x();
		v.y = vert.y();
		v.z = vert.z();
		_vertices[vertIdx.idx()] = v;
		_normals.push_back({ 0,0,0 });
		//_indices.push_back(vertIdx.idx());
	}
	for (auto& edge : ch.convexHull.edges()) {
		auto idx = ch.convexHull.vertex(edge, 0);
		_indices.push_back(idx.idx());
		idx = ch.convexHull.vertex(edge, 1);
		_indices.push_back(idx.idx());
		_indices.push_back(0xFFFF);
	}
	/*for (auto& face : ch.convexHull.faces()) {
		auto idx = ch.convexHull.halfedge(face);
		_indices.push_back(idx.idx());
		auto firstIDX = idx;
		do {
			idx = ch.convexHull.next(idx);
			_indices.push_back(idx.idx());
		} while (idx != firstIDX);
	}*/

	buildVAO();
}

void DrawConvexHull3D::drawIt() {
	setShaderProgram("algeom");
	//.setAmbient ( glm::vec3 ( .1, .3, .7 ) )
	//    .setDiffuse ( glm::vec3 ( .1, .3, .7 ) )
	//    .setEspecular ( glm::vec3 ( 1, 1, 1 ) )
	//    .setExpBright ( 100 )
	//    .apply ( glm::rotate (glm::radians(-90.0f), glm::vec3 ( 1.0f, .0f, .0f )));
	setDrawMode(TypeDraw::LINE);
	Scene::getInstance()->addModel(this);
}

void DrawConvexHull3D::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}
