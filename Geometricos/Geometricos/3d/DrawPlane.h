
/*
 * File:   DrawPlane.h
 * Author: lidia
 *
 * Created on 28 de enero de 2021, 17:11
 */

#ifndef DRAWPLANE_H
#define DRAWPLANE_H

#include "../Scene.h"
#include "Plane.h"
#include "../Draw.h"


class DrawPlane : public Draw {

	Plane dt;

public:

	DrawPlane(Plane& t);

	DrawPlane(const DrawPlane& ddt) : dt(ddt.dt), Draw() {}

	void drawIt();
	void drawIt(TypeColor c);
	void drawIt(glm::vec4 c);

	virtual ~DrawPlane() {};
};

#endif /* DRAWPLANE_H */

