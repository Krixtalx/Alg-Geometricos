#pragma once
#include "Draw.h"
#include "TDelaunay.h"

class DrawTDelaunay : public Draw {
public:
	DrawTDelaunay(const TDelaunay& t);

	DrawTDelaunay(const DrawTDelaunay& ddt) :  Draw(ddt) {
	};

	void drawIt();
	void drawIt(TypeColor c);
};