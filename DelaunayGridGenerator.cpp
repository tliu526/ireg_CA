/*
Implementation of the Delaunay Grid Generator. Utilizes the "flip" algorithm to construct a triangulation:
An arbitrary triangulation is constructed, and illegal edges are flipped until all edges are valid delaunay
edges. The flip algorithm runs in O(n^2) time; faster algorithms (the "iterative" algorithm runs in 
O(nlog(n))) require more complicated data structures to maintain. If performance becomes an issue we can 
revist the implementation for improvements.

References:
https://www.cs.duke.edu/courses/fall08/cps230/Lectures/L-21.pdf

We have approximately n^2 scaling, 1000 points takes 2.1 seconds, 4000 points takes ~2 min. Not great.
Need to look at optimizing some of the other functions, or switching to an alternative algorithm.

(c) Tony Liu 2015.
*/
#include "DelaunayGridGenerator.h"

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <utility>

using namespace std;

DelaunayGridGenerator::DelaunayGridGenerator(vector<Point> &pts, float x, float y) : GridGenerator(pts, x, y) {
	verts = pts;
	init_triangulation();
	delaunay_triangulation();
	init_maps();
	generate_graph();
	grid_type = "Delaunay";
}

DelaunayGridGenerator::DelaunayGridGenerator(std::string file) : GridGenerator(file) {
	grid_type = "Delaunay";
};

bool point_xcomparator(Point a, Point b){
	return a.x < b.x;
};

void DelaunayGridGenerator::generate_graph() {

	typename map<Point, string>::iterator map_it;
	for(map_it = rev_gen_pt_map.begin(); map_it != rev_gen_pt_map.end(); map_it++) {
		graph.add_vertex(map_it->second, Cell(map_it->first, map_it->second));		
	}

	for (int i = 0; i < edges.size(); i++){
		string p1 = rev_gen_pt_map[edges[i].p];
		string p2 = rev_gen_pt_map[edges[i].q];
		graph.add_edge(p1,p2);
	}

	//graph.print_adj_list();
}

//can be improved, how can we determine visibility quicker?
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

//horribly slow 
void DelaunayGridGenerator::add_tris(Point anchor, std::vector<Edge> &new_edges){
	//walk through all pairs of new edges, see if there is a corresponding edge that can be added
	for (int i = 0; i < new_edges.size(); i++){
		for (int j = 0; j < new_edges.size(); j++){
			if(i != j){
				Edge e1 = new_edges[i];
				Edge e2 = new_edges[j];
				Point p1;
				Point p2;

				if(e1.p == anchor) 
					p1 = e1.q;
				else
					p1 = e1.p;

				if(e2.p == anchor) 
					p2 = e2.q;
				else
					p2 = e2.p;

				Edge e3(p1, p2);
				//cout << "existing edge? " << e3 << endl;
				if(count(edges.begin(), edges.end(), e3) > 0){
					Tri t(e1,e2,e3);
				
					if(isValidTri(t) && (count(faces.begin(), faces.end(), t) == 0)){
						faces.push_back(t);
					}
				}
			}
		}
	}
}

bool DelaunayGridGenerator::isValidTri(Tri &t){

	for(int i = 0; i < gen_pts.size(); i++){
		if (!t.contains_vert(gen_pts[i])) {
			if (pt_in_tri(gen_pts[i], t)) {
				return false;
			}
		}
	}

	return true;
}

vector<Edge> DelaunayGridGenerator::init_triangulation() {

	//TODO get rid of xcomparator
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

		add_tris(gen_pts[i], new_edges);
		edges.insert(edges.end(), new_edges.begin(), new_edges.end());
		new_edges.clear();
	}

	return edges;
}

bool DelaunayGridGenerator::is_locally_delaunay(Edge e, Tri t1, Tri t2){
	Point pt;

	for(int i = 0 ; i < t1.verts.size(); i++){
		if(!e.contains(t1.verts[i])){
			pt = t1.verts[i];
			break;
		}
	}

	return !pt_in_circumcircle(pt, t2);
}

void DelaunayGridGenerator::flip_edge(Edge e, Tri t1, Tri t2){
	Point p1;
	Point p2;

	for(int i = 0; i < t1.verts.size(); i++){
		if(!e.contains(t1.verts[i])){
			p1 = t1.verts[i];
			break;
		}
	}

	for(int i = 0; i < t2.verts.size(); i++){
		if(!e.contains(t2.verts[i])){
			p2 = t2.verts[i];
			break;
		}
	}
	Edge new_e(p1,p2);

	faces.erase(remove(faces.begin(), faces.end(), t1), faces.end());
	faces.erase(remove(faces.begin(), faces.end(), t2), faces.end());

	Tri new_t1(new_e, Edge(p1,e.p), Edge(p2, e.p));
	Tri new_t2(new_e, Edge(p1,e.q), Edge(p2, e.q));

	faces.push_back(new_t1);
	faces.push_back(new_t2);

	edges.erase(remove(edges.begin(), edges.end(), e), edges.end());
	edges.push_back(new_e);

	//sanity check
	if(pt_in_circumcircle(e.p, new_t2) || pt_in_circumcircle(e.q, new_t1)) {
		cout << "something horrible has happened" << endl;
	}
}

void DelaunayGridGenerator::delaunay_triangulation() {
	vector<Edge> marked = edges;

	stack<Edge, vector<Edge> > edge_stack(marked);

	while (!edge_stack.empty()){
		//cout << "stack size: " << edge_stack.size() << endl;
		Edge e = edge_stack.top();
		edge_stack.pop();
		marked.erase(remove(marked.begin(), marked.end(), e), marked.end());

		Tri *t1 = NULL;
		Tri *t2 = NULL;

		//is there a better way to do this?
		int i;
		for(i = 0; i < faces.size(); i++) {
			if(faces[i].contains_edge(e)) {
				t1 = (Tri*)&faces[i];
				i++;
				break;
			}
		}

		for(i; i < faces.size(); i++) {
			if (faces[i].contains_edge(e)) {
				t2 = (Tri*)&faces[i];
				break;
			}
		}

		//if we find another tri with the shared edge, could be a border edge
		if (t2 != NULL){
			if(!is_locally_delaunay(e, *t1, *t2)){

				for(int i = 0; i < t1->edges.size(); i++){
					if((e != t1->edges[i]) && (count(marked.begin(), marked.end(), t1->edges[i]) == 0)){
						marked.push_back(t1->edges[i]);
						edge_stack.push(t1->edges[i]);
					}
				}

				for(int i = 0; i < t2->edges.size(); i++){
					if((e != t2->edges[i]) && (count(marked.begin(), marked.end(), t2->edges[i]) == 0)){
						marked.push_back(t2->edges[i]);
						edge_stack.push(t2->edges[i]);
					}
				}

				flip_edge(e, *t1, *t2);
			}
		}
	}
}

// for debugging
int main() {
/*
	Point p1(1,2);
	Point p2(4,7);
	Point p3(-5,10);

	Tri t(Edge(p2,p1), Edge(p2,p3), Edge(p3,p1));
	cout << "Circumcenter: " << get_circumcenter(t) << endl;
	return 0;
*/
	//vector<Point> pts = generate_uniform_rand(1000, 70, 70);
	//DelaunayGridGenerator gen(pts, 70, 70);
	
	//cout << "After Delaunay Triangulation" << endl;
	//cout << "Number of faces: " << gen.faces.size() << endl;
	//cout << "Number of edges: " << gen.edges.size() << endl;

	//gen.grid_to_file("test.txt");
	//gen.grid_to_dot("test");
	
	DelaunayGridGenerator gen("test.txt");
	gen.grid_to_file("test_from_file.txt");
	gen.grid_to_dot("test_from_file");
}