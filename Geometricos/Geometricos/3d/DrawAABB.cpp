#include "DrawAABB.h"
#include "DrawSegment3d.h"


DrawAABB::DrawAABB(AABB& t) : _aabb(t), Draw() {

	//XXXX


	buildVAO();

}


void DrawAABB::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}


void DrawAABB::drawIt() {

	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PolygonGeo);
	Scene::getInstance()->addModel(this);

	//    for (int i=0; i<dsegment.size(); i++)
	//        dsegment[i].drawIt();

}

