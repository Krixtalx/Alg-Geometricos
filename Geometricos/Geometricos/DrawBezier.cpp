#include "DrawBezier.h"
#include "Scene.h"

DrawBezier::DrawBezier(Bezier& bez) : dt(bez), Draw()
{
	unsigned i = 0;
	for (float t = 0; t < 1; t += 0.02f) {
		Point aux = bez.calcularPunto(t);

		if (!(BasicGeometry::equal(aux.getX(), aux.getX() && BasicGeometry::equal(aux.getX(), BasicGeometry::INFINITO)))) {
			_vertices.push_back(glm::vec3(aux.getX(), aux.getY(), 0));

			_normals.push_back(glm::vec3(0, 0, 1));

			_indices.push_back(i++);
		}
	}

	buildVAO();
}

void DrawBezier::drawIt()
{
	setShaderProgram("algeom");
	setDrawMode(TypeDraw::LINE);
	Scene::getInstance()->addModel(this);
}

void DrawBezier::drawIt(TypeColor c)
{
	setColorActivo(c);
	drawIt();
}
