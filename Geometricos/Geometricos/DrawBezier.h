#pragma once
#include "Draw.h"
#include "Bezier.h"

class DrawBezier : public Draw {
	Bezier dt;

public:

	DrawBezier(Bezier& t);

	DrawBezier(const DrawBezier& ddt) : dt(ddt.dt), Draw() {}

	void drawIt();
	void drawIt(TypeColor c);

	virtual ~DrawBezier() {};
};

