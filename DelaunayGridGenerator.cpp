/*
Implementation of the Delaunay Grid Generator. Utilizes the "flip" algorithm to construct a triangulation:
An arbitrary triangulation is constructed, and illegal edges are flipped until all edges are valid delaunay
edges. The flip algorithm runs in O(n^2) time; faster algorithms (the "iterative" algorithm runs in O(nlog(n)))
require more complicated data structures to maintain. If performance becomes an issue we can revist the 
implementation for improvements.

References:
https://www.cs.duke.edu/courses/fall08/cps230/Lectures/L-21.pdf

(c) Tony Liu 2015.
*/
#include "DelaunayGridGenerator.h"

#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

DelaunayGridGenerator::DelaunayGridGenerator(vector<Point> &pts) : GridGenerator(pts) {
	//TODO add initialization here?
}

bool point_xcomparator(Point a, Point b){
	return a.x < b.x;
};

void DelaunayGridGenerator::generate_graph() {
	//TODO
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

	faces.erase(remove(faces.begin(), faces.end(), t1), faces.end());
	faces.erase(remove(faces.begin(), faces.end(), t2), faces.end());
	Tri new_t1(p1,e.p,e.q);
	Tri new_t2(p2,e.p,e.q);

	faces.push_back(Tri(p1,e.p,e.q));
	faces.push_back(Tri(p2,e.p,e.q));

	edges.erase(remove(edges.begin(), edges.end(), e), edges.end());
	edges.push_back(Edge(p1,p2));

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
		//TODO ugly
		int i;
		for(i = 0; i < faces.size(); i++) {
			if(faces[i].contains_edge(e)) {
				t1 = &faces[i];
				i++;
				break;
			}
		}

		for(i; i < faces.size(); i++) {
			if (faces[i].contains_edge(e)) {
				t2 = &faces[i];
				break;
			}
		}

		//if we find another tri with the shared edge, could be a border edge
		if (t2 != NULL){
			if(!is_locally_delaunay(e, *t1, *t2)){
			    //push unmarked edges on the perimeter, is this necessary?
			    /*
				for(int i = 0; i < t1->edges.size(); i++){
					if((e != t1->edges[i]) && (count(marked.begin(), marked.end(), t1->edges[i]) == 0)){
						marked.push_back(t1->edges[i]);
						edge_stack.push(t1->edges[i]);
						cout << "e: " << e << endl;
						cout << "Pushed edge (t1): " << t1->edges[i] << endl;
					}
				}

				for(int i = 0; i < t2->edges.size(); i++){
					if((e != t2->edges[i]) && (count(marked.begin(), marked.end(), t2->edges[i]) == 0)){
						marked.push_back(t2->edges[i]);
						edge_stack.push(t2->edges[i]);
						cout << "t2: " << *t2 << endl;
						cout << "e: " << e << endl;
						cout << "Pushed edge (t2): " << t2->edges[i] << endl;		
						cout << endl;
					}
				}
	            */
				flip_edge(e, *t1, *t2);
			}
		}
	}
}

vector<Tri> DelaunayGridGenerator::get_faces(){
	return faces;
}

// for debugging
int main() {
	vector<Point> pts = generate_uniform_rand(4000, 50.0, 50.0);
	DelaunayGridGenerator gen(pts);
	vector<Edge> edges = gen.init_triangulation();
	/*
	for (int i = 0; i < pts.size(); i++){
		cout << pts[i] << endl;
	}

	for (int i = 0; i < edges.size(); i++){
		cout << edges[i] << endl;
	}

	cout << edges.size() << endl;	

	vector<Tri> faces = gen.get_faces();
	for (int i = 0; i < faces.size(); i++){
		cout << faces[i] << endl;
	}

	cout << "Delaunay testing: " << endl;
	*/
	gen.delaunay_triangulation();
/*
	faces = gen.get_faces();
	for (int i = 0; i < faces.size(); i++){
		cout << faces[i] << endl;
	}
*/
	vector<Tri> faces = gen.get_faces();
	cout << "Number of faces: " << faces.size() << endl;
	cout << "Number of edges: " << edges.size() << endl;
}