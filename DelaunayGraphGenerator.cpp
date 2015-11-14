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
#include <iostream>

using namespace std;

bool point_xcomparator(Point a, Point b){
	return a.x < b.x;
};

void DelaunayGraphGenerator::generate_graph() {
	//TODO
}

// determines whether point q is visible from point p, ie the edge pq does not intersect other edges
//TODO can be improved, how can we determine visibility quicker?
bool DelaunayGraphGenerator::isVisible(Point p, Point q, vector<Edge> &edge_vec){
	Edge e(p, q);

	//traverse backwards because we're more likely to hit recently added edges
	for (int i = edge_vec.size()-1; i >= 0; i--) {
		
		//don't consider edges with the same points
		if((p != edge_vec[i].p)) && (p != edge_vec[i].q) &&
			(q != edge_vec[i].p) && (q != edge_vec[i].q)){
			if (edge_intersect(edge_vec[i], e)) {
				return false;
			}
		}
	}
	return true;
}

vector<Edge> DelaunayGraphGenerator::init_triangulation() {
	vector<Edge> edge_vec;

	sort(points.begin(), points.end(), point_xcomparator); //sort by x_coord

	//Initialize by adding the "leftmost" triangle
	edge_vec.push_back(Edge(points[0], points[1]));
	edge_vec.push_back(Edge(points[0], points[2]));
	edge_vec.push_back(Edge(points[1], points[2]));

	//add all edges where the point is visible 
	for(int i = 3; i < points.size(); i++) {
		for(int j = 0; j < i; j++){
			if(isVisible(points[i], points[j], edge_vec)) {
				edge_vec.push_back(Edge(points[j], points[i]));
			}
		}
	}

	return edge_vec;
}


// for debugging
int main() {
	vector<Point> pts = generate_uniform_rand(5, 10, 10);
	DelaunayGraphGenerator gen(pts);
	vector<Edge> edges = gen.init_triangulation();

	
	for (int i = 0; i < pts.size(); i++){
		cout << pts[i] << endl;
	}

	for (int i = 0; i < edges.size(); i++){
		cout << edges[i] << endl;
	}

	cout << edges.size();
	
}