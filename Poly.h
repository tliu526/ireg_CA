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

		/**
		Determines whether or not the given edges form a valid polygon
		*/
		bool is_valid_poly();

		/**
		Returns the area of the polygon
		*/
		float get_area() const;

		bool operator==(const Poly &p);
		bool operator< (const Poly &p) const;

		bool shares_edge(Poly &p);
		bool shares_vert(Poly &p);

		friend std::ostream & operator<<(std::ostream &_stream, Poly const &p){
			_stream << "Verts: "; 
			for(size_t i = 0; i < p.verts.size(); i++){
				_stream << p.verts[i] << " ";
			}

			return _stream;
        }
};

#endif