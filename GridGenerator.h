/*
An abstract class for generating grids. This includes the graph representation, the polygons, points, 
and edges.

(c) Tony Liu 2015.
*/
#ifndef GRIDGENERATOR_H
#define GRIDGENERATOR_H

#include "util.h"
#include "Graph.h"
#include "Cell.h"
#include "Poly.h"
#include <vector>
#include <string>

class GridGenerator {
public:
	GridGenerator(std::vector<Point>& p);

	virtual void generate_graph() = 0;
	void grid_to_file(std::string f);
	
	//TODO make this work
	std::vector<Poly> get_faces();
protected:
	std::vector<Point> gen_pts; //The generator points for the grid
	std::vector<Point> verts;
	std::vector<Edge>  edges;
	std::vector<Poly>  faces;
	Graph<std::string, Cell> graph;

};

#endif