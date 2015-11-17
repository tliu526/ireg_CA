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
#include <iostream>
	
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

		bool operator==(const Poly &p);
		bool operator< (const Poly &p) const;

		friend std::ostream & operator<<(std::ostream &_stream, Poly const &p){
			_stream << "Verts: "; 
			for(int i = 0; i < p.verts.size(); i++){
				_stream << p.verts[i] << " ";
			}

			return _stream;
        }
};

#endif