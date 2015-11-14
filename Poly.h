/*
Polygon class. Primarily concerned with geometric features. Intended to be subclassed.
TODO:
- convex hull?

(c) 2015 Tony Liu.
*/
#ifndef POLY_H
#define POLY_H

#include "Edge.h"

#include <vector>
	
class Poly {
	public:
		Poly(std::vector<Edge> &in_edges);
		Poly() {};

		std::vector<Point> verts;
		std::vector<Edge> edges;

		int num_edges;
		int num_verts;

		bool contains_vert(Point &p);
		bool contains_edge(Edge &e);
};

#endif