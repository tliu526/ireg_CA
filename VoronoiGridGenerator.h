/*
A GridGenerator that generates a Voronoi diagram. Can read in the data file of a
Delaunay triangulation.

(c) 2015 Tony Liu.
*/
#ifndef VORONOIGRIDGENERATOR_H
#define VORONOIGRIDGENERATOR_H

#include "GridGenerator.h"

#include <string>

class VoronoiGridGenerator : public GridGenerator {
	public:
		VoronoiGridGenerator(std::string file);

		void generate_graph();

	private:
}