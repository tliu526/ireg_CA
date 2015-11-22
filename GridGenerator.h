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
	GridGenerator(std::string file); //reads from data file TODO needed?
	GridGenerator() {};

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

	std::map <std::string, Point> pt_map;
	std::map <std::string, Edge> edge_map;
	//std::map <std::string, Poly> face_map;
	
	std::map<Point, std::string> rev_vert_map; //for polygonal representation
	std::map<Point, std::string> rev_gen_pt_map; //for graph representation
	std::map<Edge, std::string> rev_edge_map; //associated with verts
	//std::map<Poly, std::string> rev_face_map;
};

#endif