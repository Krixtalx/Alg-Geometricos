#include "Bezier.h"
#include <iostream>

/**
 * Calcula el coeficiente binomial de manera recursiva. Basado en el triangulo de Pascal: https://es.wikipedia.org/wiki/Triángulo_de_Pascal.
 * 
 * @param n 
 * @param k
 * @return resultado del calculo
 */
unsigned Bezier::computeNK(unsigned n, unsigned k)
{
	if (n >= 0 && k == 0)
		return 1;
	if (n == 0)
		return 0;
	return computeNK(n - 1, k - 1) + computeNK(n - 1, k);
}

Bezier::Bezier()
{
}

Bezier::Bezier(std::vector<Vect2d> puntos) : puntos(puntos)
{
}

void Bezier::addPunto(Vect2d punto)
{
	puntos.push_back(punto);
}

Point Bezier::calcularPunto(float t)
{
	Vect2d p(0, 0);
	if (0 <= t && t <= 1) {
		unsigned n = puntos.size() - 1;
		for (size_t i = 0; i < n + 1; i++) {
			unsigned nk = computeNK(n, i);
			float scalar = std::powf(1 - t, n - i) * std::powf(t, i);
			Vect2d aux = puntos[i];
			aux = aux.scalarMult(nk * scalar);
			p = p.add(aux);
		}
	} else {
		p.set(BasicGeometry::INFINITO, BasicGeometry::INFINITO);
	}
	return p;
}