/*
Implementation of the Delaunay Graph Generator. Utilizes the "flip" algorithm to construct a triangulation:
An arbitrary triangulation is constructed, and illegal edges are flipped until all edges are valid delaunay
edges. The flip algorithm runs in O(n^2) time; faster algorithms (the "iterative" algorithm runs in O(nlog(n)))
require more complicated data structure to maintain. If performance becomes an issue we can revist the 
implementation for improvements.

(c) Tony Liu 2015.
*/
#include "DelaunayGraphGenerator.h"

#include <algorithm>

using namespace std;

bool point_xcomparator(point a, point b){
	return a.x < b.x;
};

void DelaunayGraphGenerator::generate_graph() {
	//TODO
}

vector<edge> DelaunayGraphGenerator::init_triangulation() {
	vector<edge> edge_vec;

	sort(points.begin(), points.end(), point_xcomparator); //sort by x_coord

	//Initialize by adding the "leftmost" triangle
	vec.pushback(edge(points[0], points[1]));
	vec.pushback(edge(points[0], points[2]));
	vec.pushback(edge(points[1], points[2]));

	for(int i = 3; i < points.size(); i++) {
		for(int j = 0; j < i; i++){
			if(isVisible(points[i], points[j], edge_vec)) {
				vec.pushback(edge(points[j], points[i]))
			}
		}
	}

	return edge_vec;
}

// determines whether point q is visible from point p, ie the edge pq does not intersect other edges
//TODO can be improved, how can we determine visibility quicker?
bool isVisible(point p, point q, vector<edge> &edge_vec){
	edge e(p, q);
	//traverse backwards because we're more likely to hit recently added edges
	for (int i = edge_vec.size()-1; i >= 0; i--) {
		if (edge_intersect(edge_vec[i], e) {
			return false;
		}
	}

	return true;
}

// for debugging
int main() {


}