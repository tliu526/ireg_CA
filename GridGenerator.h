/*
An abstract class for generating grids. This includes the graph representation, the polygons, points, 
and edges.

TODO: a connection between faces and gen points?

(c) Tony Liu 2015.
*/
#ifndef GRIDGENERATOR_H
#define GRIDGENERATOR_H

#include "util.h"
#include "Graph.h"
#include "Cell.h"
#include "Poly.h"
#include "Property.h"

#include <vector>
#include <string>
#include <map>

class GridGenerator {
public:
	//string constants for finding the state property in the cell
	static const std::string B_STATE;
	static const std::string I_STATE;
	static const std::string F_STATE;

	GridGenerator(std::vector<Point>& p, float min_x, float max_x, float min_y, float max_y); // defines starting grid of size 2x by 2y
	GridGenerator(std::string file); //reads from data file
	GridGenerator() {};

	virtual void generate_graph(); 
	virtual void map_faces(); //populates the gen_pt_face_map

	void grid_to_file(std::string f);
	void grid_to_dot(std::string out_name); //converts the grid to a (neato) graphviz file
	void graph_to_dot(std::string out_name); //converts the graph to a neato graphviz file	

	std::vector<Poly> get_faces();
	Graph<std::string, Cell> *get_graph();
	bool pt_in_grid(Point p); //checks whether p lies within the bounds of the grid, border points return false

	//Builds property according to the labels
	Property build_property(std::string& label, std::string& value); 
protected:
	/**
	initializes pt, edge, face maps
	pre: verts, edges, faces are initialized
	*/
	void init_maps(); 
	
	/**
	initializes the grid generator from file
	*/
	void init_from_file(std::string file); 

	std::string grid_type;
	float min_x, max_x, min_y, max_y; //For defining bounds on the grid

	std::vector<Point> gen_pts; //The generator points for the grid
	std::vector<Point> verts;
	std::vector<Edge>  edges;
	std::vector<Poly>  faces;
	
	Graph<std::string, Cell> graph;

	std::map <std::string, Point> pt_map;
	std::map <std::string, Edge> edge_map;
	std::map <std::string, Poly> face_map;
	std::map <std::string, std::string> gen_pt_face_map; //(gen_pt label, face label) map
	
	std::map<Point, std::string> rev_vert_map; //for polygonal representation
	std::map<Point, std::string> rev_gen_pt_map; //for graph representation
	std::map<Edge, std::string> rev_edge_map; //associated with verts
};

#endif