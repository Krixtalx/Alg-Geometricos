#pragma once
#include "Draw.h"
#include "ConvexHull3D.h"
class DrawConvexHull3D : public Draw {
public:
	DrawConvexHull3D(const ConvexHull3D& ch);

	DrawConvexHull3D(const DrawConvexHull3D& dch) : Draw(dch) {
	};

	void drawIt();
	void drawIt(TypeColor c);
};

