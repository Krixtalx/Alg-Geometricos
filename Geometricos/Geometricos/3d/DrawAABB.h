
/*
 * File:   DrawAABB.h
 * Author: lidia
 *
 * Created on 27 de enero de 2021, 19:32
 */

#ifndef DRAWAABB_H
#define DRAWAABB_H


#include <vector>
#include "../Scene.h"
#include "AABB.h"
#include "../Draw.h"
#include "DrawSegment3d.h"


class DrawAABB : public Draw {

	AABB _aabb;
	std::vector<DrawSegment3d> dsegment;

public:
	friend class AABB;

	DrawAABB(AABB& t);

	DrawAABB(const DrawAABB& dt) : _aabb(dt._aabb), dsegment(dt.dsegment), Draw() {}

	void drawIt();
	void drawIt(TypeColor c);

	virtual ~DrawAABB() {};
};

#endif /* DRAWAABB_H */

