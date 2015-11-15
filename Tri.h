/*
Triangle class, holding both points and edges. Extends the Poly class.

*/
#ifndef TRI_H
#define TRI_H

#include "Poly.h"

class Tri : public Poly {
	public:
		Tri(Edge e1, Edge e2, Edge e3);
		Tri(Point p1, Point p2, Point p3);
		Tri() {};

};

#endif