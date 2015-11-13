/*
A GraphGenerator that generates a graph with a Delaunay triangulation.

Things to think about:
- How do we reuse computation for the subsequent polygon generations (Voronoi, Voronoi-Quads)?

(c) Tony Liu 2015.
*/

#ifndef DELAUNAYGRAPHGENERATOR_H
#define DELAUNAYGRAPHGENERATOR_H

#include "util.h"
#include "GraphGenerator.h"

#include <vector>

class DelaunayGraphGenerator : public GraphGenerator {
	public:
		void generate_graph();

	private:
		//generates a list of edges that gives an arbitrary triangulation using an incremental process
		std::vector<edge> init_triangulation(); 
		// determines whether point q is visible from point p, ie the edge pq does not intersect other edges
		//bool              isVisible(point p, point q, vector<edge> &edge_vec); 
};

#endif