#pragma once
#include <vector>
#include "Vect2d.h"


class Bezier {
	std::vector<Vect2d> puntos;
	unsigned computeNK(unsigned n, unsigned k);

public:
	Bezier();
	Bezier(std::vector<Vect2d> puntos);

	void addPunto(Vect2d punto);
	Point calcularPunto(float t);
};
