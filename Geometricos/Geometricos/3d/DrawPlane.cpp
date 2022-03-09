
/*
 * File:   DrawPlane.cpp
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 17:11
 */


#include "DrawPlane.h"




DrawPlane::DrawPlane(Plane& t) : dt(t), Draw() {
	Line3d line(t._a, t._b);
	Line3d line2(t._a, t._c);
	Line3d line3(t._b, t._c);
	Vect3d normal = t.getNormal();
	this->_vertices.push_back(line.getPoint(-5).toGLM());
	this->_vertices.push_back(line.getPoint(5).toGLM());
	this->_vertices.push_back(line2.getPoint(5).toGLM());
	this->_vertices.push_back(line3.getPoint(5).toGLM());

	for (size_t i = 0; i < 4; i++) {
		_indices.push_back(i);
		_normals.push_back(normal.toGLM());
	}
	buildVAO();

}


void DrawPlane::drawIt(TypeColor c) {
	setColorActivo(c);
	drawIt();
}


void DrawPlane::drawIt() {
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PolygonGeo);
	Scene::getInstance()->addModel(this);

}

