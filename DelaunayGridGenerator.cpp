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

//TODO can be improved, how can we determine visibility quicker?
bool DelaunayGridGenerator::isVisible(Point p, Point q){
	Edge e(p, q);

	//traverse backwards because we're more likely to hit recently added edges
	for (int i = edges.size()-1; i >= 0; i--) {
		
		//don't consider edges with the same points
		if((p != edges[i].p) && (p != edges[i].q) &&
			(q != edges[i].p) && (q != edges[i].q)){
			if (edge_intersect(edges[i], e)) {
				return false;
			}
		}
	}
	return true;
}

void DelaunayGridGenerator::add_tris(std::vector<Edge> &new_edges){
	//walk through all pairs of new edges, see if there is a corresponding edge that can
	for (int i = 0; i < new_edges.size(); i++){
		for (int j = 0; j < new_edges.size(); j++){
			if(i != j){
				//TODO
			}
		}
	}
}

vector<Edge> DelaunayGridGenerator::init_triangulation() {

	sort(gen_pts.begin(), gen_pts.end(), point_xcomparator); //sort by x_coord

	//Initialize by adding the "leftmost" triangle
	Edge e1(gen_pts[0], gen_pts[1]);
	Edge e2(gen_pts[0], gen_pts[2]);
	Edge e3(gen_pts[1], gen_pts[2]);
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	faces.push_back(Tri(e1,e2,e3));

	vector<Edge> new_edges;
	//add all edges where the point is visible 
	for(int i = 3; i < gen_pts.size(); i++) {

		for(int j = 0; j < i; j++){
			if(isVisible(gen_pts[i], gen_pts[j])) {
				new_edges.push_back(Edge(gen_pts[j], gen_pts[i]));
			}
		}
		add_tris(new_edges);
		edges.insert(edges.end(), new_edges.begin(), new_edges.end());
		new_edges.clear();
	}

	return edges;
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