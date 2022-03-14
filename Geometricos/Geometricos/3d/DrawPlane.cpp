
/*
 * File:   DrawPlane.cpp
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 17:11
 */


#include "DrawPlane.h"




DrawPlane::DrawPlane(Plane& t) : dt(t), Draw() {
	/*Vect3d aux(t._b.add(t._c.sub(t._a)));
	this->_vertices.push_back(t._a.toGLM());
	this->_vertices.push_back(t._b.toGLM());
	this->_vertices.push_back(t._c.toGLM());
	this->_vertices.push_back(aux.toGLM());*/
	Line3d lineA(t._a, t._b);
	Line3d lineB(t._a, t._c);
	this->_vertices.push_back(lineA.getPoint(-5).toGLM());
	this->_vertices.push_back(lineA.getPoint(5).toGLM());
	this->_vertices.push_back(lineB.getPoint(-5).toGLM());
	this->_vertices.push_back(lineB.getPoint(5).toGLM());

	_indices.push_back(0);
	_indices.push_back(2);
	_indices.push_back(1);
	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(3);

	Vect3d normal = t.getNormal();
	for (size_t i = 0; i < 4; i++) {
		//_indices.push_back(i);
		_normals.push_back(normal.toGLM());
	}
	buildVAO();

}


void DrawPlane::drawIt(TypeColor c) {
	setColorActivo(c);
	setAmbient(glm::vec3(c.R, c.G, c.B));
	drawIt();
}

void DrawPlane::drawIt(glm::vec4 c) {
	setColorActivo({ c });
	setAmbient(c);
	drawIt();
}



void DrawPlane::drawIt() {
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::PLAIN);
	Scene::getInstance()->addModel(this);

}

