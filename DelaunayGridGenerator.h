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

		std::vector<Tri> get_faces();

	    //TODO only here for debugging
	    /*
	    generates a list of edges that gives an arbitrary triangulation using an incremental process
		*/
		std::vector<Edge> init_triangulation(); 
		
		//TODO only here for debuggin
		/*
	    Once the edges and triangulations are initialized, generates a delaunay triangulation.
		*/
		void delaunay_triangulation();
	private:
		std::vector<Tri> faces;
		/*
		Determines whether point q is visible from point p, i.e. the edge pq does not intersect other edges.
		*/
		bool isVisible(Point p, Point q);

		/*
		Adds tris to the face vector when considering the new edges.
		@param anchor: the point that will be contained in the all the new triangles, the base of the "fan"
	    @param new_edges: the newly added edges that include the anchor
	    */
		void add_tris(Point anchor, std::vector<Edge> &new_edges);

		/*
		Checks whether the triangles t1 and t2 are locally delaunay against the shared edge e.
		@pre: e is shared between t1 and t2
		*/
		bool is_locally_delaunay(Edge e, Tri t1, Tri t2);

		/*
		Flips a common edge e between a quad defined by two tris in the graph. Edits the edges vector and 
		faces vector accordingly.
		*/
		void flip_edge(Edge e, Tri t1, Tri t2);

		/*
	    Checks whether the given tri is valid (doesn't contain any of the other points in the grid)
		*/
		bool isValidTri(Tri &t);
};

#endif