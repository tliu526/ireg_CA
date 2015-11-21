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
#include <map>

class GridGenerator {
public:
	GridGenerator(std::vector<Point>& p);

	virtual void generate_graph() = 0;
	void grid_to_file(std::string f);
	void grid_to_dot(std::string out_name); //converts the grid to a (neato) graphviz file
	std::vector<Poly> get_faces();

protected:
	/*
	initializes pt, edge, face maps
	pre: verts, edges, faces are initialized
	*/
	void init_maps(); 

	std::vector<Point> gen_pts; //The generator points for the grid
	std::vector<Point> verts;
	std::vector<Edge>  edges;
	std::vector<Poly>  faces;
	
	Graph<std::string, Cell> graph;
	std::map<Point, std::string> pt_map; 
	std::map<Edge, std::string> edge_map;
	//TODO
	//std::map<Poly, std::string> face_map;
};

#endif