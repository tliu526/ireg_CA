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

class DelaunayGraphGenerator : public GraphGenerator {
	void generate_graph();
};

#endif