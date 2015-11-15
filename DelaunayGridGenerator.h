/*
A GridGenerator that generates a Grid with a Delaunay triangulation.

Things to think about:
- How do we reuse computation for the subsequent polygon generations (Voronoi, Voronoi-Quads)?

(c) Tony Liu 2015.
*/

#ifndef DELAUNAYGRIDGENERATOR_H
#define DELAUNAYGRIDGENERATOR_H

#include "GridGenerator.h"
#include "Tri.h"
#include <vector>

class DelaunayGridGenerator : public GridGenerator {
	public:
		DelaunayGridGenerator(std::vector<Point>& p);

		void generate_graph();

	    //TODO only here for debugging
	    //generates a list of edges that gives an arbitrary triangulation using an incremental process
		std::vector<Edge> init_triangulation(); 
		
	private:
		// determines whether point q is visible from point p, ie the edge pq does not intersect other edges
		bool isVisible(Point p, Point q);

		/*
		Adds tris to the face vector when considering the new edges.
		@param anchor: the point that will be contained in the all the new triangles, the base of the "fan"
	    @param new_edges: the newly added edges that include the anchor
	    */
		void add_tris(Point anchor, std::vector<Edge> &new_edges);

		/*
	    Checks whether the given tri is valid (doesn't contain any of the other points in the grid)
		*/
		bool isValidTri(Tri &t);
};

#endif