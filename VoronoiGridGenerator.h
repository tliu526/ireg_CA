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
		void init_from_file(std::string file); //initializes gen_pts, edges, pt_face_map, tri_map from delaunay file
		void init_voronoi();
		
		std::map <std::string, std::vector<std::string> > pt_face_map; // keeps track of faces the given pt is a part of
		std::map <std::string, Tri> tri_map; //for building voronoi diagrams from delaunay
};

#endif

