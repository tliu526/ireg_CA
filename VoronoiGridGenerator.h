/*
A GridGenerator that generates a Voronoi diagram. Can read in the data file of a
Delaunay triangulation.

(c) 2015 Tony Liu.
*/
#ifndef VORONOIGRIDGENERATOR_H
#define VORONOIGRIDGENERATOR_H

#include "GridGenerator.h"

#include <string>
#include <map>

class VoronoiGridGenerator : public GridGenerator {
	public:
		VoronoiGridGenerator(std::string file);

		void generate_graph();

	private:
		Edge top_border, bottom_border, left_border, right_border;
        /*
        Utilizes the fact that the circumcenter of the triangles in a delaunay triangulation are the vertices of the
        voronoi polygons.
        From: http://stackoverflow.com/questions/85275/how-do-i-derive-a-voronoi-diagram-given-its-point-set-and-its-delaunay-triangula
	    */
		void init_from_delaunay(); //called when VGG is constructed from a Delaunay data file
		void init_voronoi(); //called from init_from_delaunay
		void init_borders(); //called from init_from_delaunay


		Point clamp_pt(Point p); //Clamps a given point to the bounds of the grid
		Edge clamp_edge(Edge e); //"cuts off" a given edge by the bounds of the grid
		void add_border_edge(vector<Edge> &edges);

		Point eval_at_border(std::pair<float, float> line_params, Edge border); //evaluates the line based on the given border
		Edge closest_border(Edge e); // returns the closest border for an edge that has both points outside the bounds of the grid
		std::map <std::string, std::vector<std::string> > pt_face_map; // keeps track of faces the given pt is a part of
		std::map <std::string, Tri> tri_map; //for building voronoi diagrams from delaunay
};

#endif

