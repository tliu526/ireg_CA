/*
A GraphGenerator that generates a graph with a Delaunay triangulation.

Things to think about:
- How do we reuse computation for the subsequent polygon generations (Voronoi, Voronoi-Quads)?

(c) Tony Liu 2015.
*/

#ifndef DELAUNAYGRAPHGENERATOR_H
#define DELAUNAYGRAPHGENERATOR_H

#include "GraphGenerator.h"

#include <vector>

class DelaunayGraphGenerator : public GraphGenerator {
	public:
		explicit DelaunayGraphGenerator(std::vector<Point>& p) : GraphGenerator(p) {}

		void generate_graph();
		std::vector<Edge> init_triangulation(); 

	private:
		//generates a list of edges that gives an arbitrary triangulation using an incremental process
		
		// determines whether point q is visible from point p, ie the edge pq does not intersect other edges
		bool isVisible(Point p, Point q, std::vector<Edge> &edge_vec);
};

#endif