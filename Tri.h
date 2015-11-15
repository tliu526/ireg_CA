/*
Triangle class, holding both points and edges. Extends the Poly class.

*/
#ifndef TRI_H
#define TRI_H

#include "Poly.h"

class Tri : public Poly {
	public:
		Tri(Edge e1, Edge e2, Edge e3);

		bool operator==(const Tri& tri);

};

#endif