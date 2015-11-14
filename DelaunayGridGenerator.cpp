/*
Implementation of the Delaunay Grid Generator. Utilizes the "flip" algorithm to construct a triangulation:
An arbitrary triangulation is constructed, and illegal edges are flipped until all edges are valid delaunay
edges. The flip algorithm runs in O(n^2) time; faster algorithms (the "iterative" algorithm runs in O(nlog(n)))
require more complicated data structure to maintain. If performance becomes an issue we can revist the 
implementation for improvements.

(c) Tony Liu 2015.
*/
#include "DelaunayGridGenerator.h"

#include <algorithm>
#include <iostream>

using namespace std;

DelaunayGridGenerator::DelaunayGridGenerator(vector<Point> &pts) : GridGenerator(pts) {
	//TODO
}

bool point_xcomparator(Point a, Point b){
	return a.x < b.x;
};

void DelaunayGridGenerator::generate_graph() {
	//TODO
}

// determines whether point q is visible from point p, ie the edge pq does not intersect other edges
//TODO can be improved, how can we determine visibility quicker?
bool DelaunayGridGenerator::isVisible(Point p, Point q, vector<Edge> &edge_vec){
	Edge e(p, q);

	//traverse backwards because we're more likely to hit recently added edges
	for (int i = edge_vec.size()-1; i >= 0; i--) {
		
		//don't consider edges with the same points
		if((p != edge_vec[i].p) && (p != edge_vec[i].q) &&
			(q != edge_vec[i].p) && (q != edge_vec[i].q)){
			if (edge_intersect(edge_vec[i], e)) {
				return false;
			}
		}
	}
	return true;
}

vector<Edge> DelaunayGridGenerator::init_triangulation() {
	vector<Edge> edge_vec;

	sort(gen_pts.begin(), gen_pts.end(), point_xcomparator); //sort by x_coord

	//Initialize by adding the "leftmost" triangle
	edge_vec.push_back(Edge(gen_pts[0], gen_pts[1]));
	edge_vec.push_back(Edge(gen_pts[0], gen_pts[2]));
	edge_vec.push_back(Edge(gen_pts[1], gen_pts[2]));

	//add all edges where the point is visible 
	for(int i = 3; i < gen_pts.size(); i++) {
		for(int j = 0; j < i; j++){
			if(isVisible(gen_pts[i], gen_pts[j], edge_vec)) {
				edge_vec.push_back(Edge(gen_pts[j], gen_pts[i]));
			}
		}
	}

	return edge_vec;
}

// for debugging
int main() {
	vector<Point> pts = generate_uniform_rand(15, 50, 50);
	DelaunayGridGenerator gen(pts);
	vector<Edge> edges = gen.init_triangulation();

	
	for (int i = 0; i < pts.size(); i++){
		cout << pts[i] << endl;
	}

	for (int i = 0; i < edges.size(); i++){
		cout << edges[i] << endl;
	}

	cout << edges.size();
	
}