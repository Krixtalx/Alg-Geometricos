#include "DrawTDelaunay.h"
#include "Scene.h"

DrawTDelaunay::DrawTDelaunay(const TDelaunay& t) : Draw() {
	int q = 0;
	for (auto& face : t.dt.finite_face_handles()) {
		auto tri = t.dt.triangle(face);
		for (size_t i = 0; i < 3; i++) {
			glm::vec3 v; 
			auto p = tri[i];
			v.x = p.x();
			v.y = p.y();
			v.z = p.z();
			_vertices.push_back(v);
			_indices.push_back(q++);
			_normals.push_back({ 0,0,0 });
		}
	}
	buildVAO();
}

void DrawTDelaunay::drawIt() {
	setShaderProgram("algeom");
	//.setAmbient ( glm::vec3 ( .1, .3, .7 ) )
	//    .setDiffuse ( glm::vec3 ( .1, .3, .7 ) )
	//    .setEspecular ( glm::vec3 ( 1, 1, 1 ) )
	//    .setExpBright ( 100 )
	//    .apply ( glm::rotate (glm::radians(-90.0f), glm::vec3 ( 1.0f, .0f, .0f )));
	setDrawMode(TypeDraw::WIREFRAME);
	Scene::getInstance()->addModel(this);
}

void DrawTDelaunay::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}
