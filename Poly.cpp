/*
Implmentation of Poly class.
*/
#include "Poly.h"

#include <iostream>
#include <algorithm>

using namespace std;

Poly::Poly(vector<Edge> &in_edges){
	edges = in_edges;

	for (int i = 0; i < edges.size(); i++){
		if(count(verts.begin(), verts.end(), edges[i].p) == 0)
			verts.push_back(edges[i].p);

		if(count(verts.begin(), verts.end(), edges[i].q) == 0)
			verts.push_back(edges[i].q);
	}

	sort(verts.begin(), verts.end());
	sort(edges.begin(), edges.end());

	num_edges = edges.size();
	num_verts = verts.size();
}

bool Poly::contains_edge(Edge &e){
	return count(edges.begin(), edges.end(), e) > 0;
}

bool Poly::contains_vert(Point &p){
	return count(verts.begin(), verts.end(), p) > 0;
}

bool Poly::operator==(const Poly& poly){

	for(int i = 0; i < poly.verts.size(); i++){
		if(count(verts.begin(), verts.end(), poly.verts[i]) == 0){
			return false;
		}
	}

	return true;
}


bool Poly::shares_edge(Poly &poly){
	for(int i = 0; i < edges.size(); i++){
		if(count(poly.edges.begin(), poly.edges.end(), edges[i]) > 0){
			return true;
		}
	}

	return false;
}

//TODO comparisons should be made via area
bool Poly::operator< (const Poly &poly) const {
	return false;
}
/*
int main() {
	vector<Edge> edges;
	Point p1(0,0);
	Point p2(0,1);
	Point p3(1,1);
	Point p4(1,0);

	Edge e1(p1,p2);
	Edge e2(p2,p3);
	Edge e3(p3,p4);
	Edge e4(p1,p4);

	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	edges.push_back(e4);

	Poly p(edges);
	vector<Point> *pts = &p.verts;
	for (int i = 0; i < pts->size(); i++) {
		cout << (*pts)[i] << endl;
	}

	cout << p.contains_vert(p1) << endl;
	cout << p.contains_edge(e1) << endl;
}
*/