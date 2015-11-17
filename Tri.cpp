/*
Implementation of the Tri class.

(c) 2015 Tony Liu.
*/
#include "Tri.h"
#include "util.h"

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

Tri::Tri(Edge e1, Edge e2, Edge e3) {
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);

	for (int i = 0; i < edges.size(); i++){
		if(count(verts.begin(), verts.end(), edges[i].p) == 0)
			verts.push_back(Point(edges[i].p));

		if(count(verts.begin(), verts.end(), edges[i].q) == 0)
			verts.push_back(Point(edges[i].q));
	}

	num_edges = edges.size();
	num_verts = verts.size();

	if (num_verts != 3)
		throw invalid_argument("The edges provided do not form a tri");
}

//TODO sanity checks?
Tri::Tri(Point p1, Point p2, Point p3){
	verts.push_back(p1);
	verts.push_back(p2);
	verts.push_back(p3);

	edges.push_back(Edge(p1,p2));
	edges.push_back(Edge(p2,p3));
	edges.push_back(Edge(p1,p3));

	num_edges = edges.size();
	num_verts = verts.size();
}

/*
int main(){
	Point p1(0,0);
	Point p2(0,3);
	Point p3(3,3);

	Edge e1(p1,p2);
	Edge e2(p2,p3);
	Edge e3(p1,p3);

	Edge test(p2,p1);

	Tri t1(e1, e2, e3);
	Tri t2(p1, p2, p3);

	vector<Point> *pts = &t1.verts;
	for (int i = 0; i < pts->size(); i++) {
		cout << (*pts)[i] << endl;
	}
	cout << "equality:" << (t1==t2) << endl;
	cout << t1.contains_vert(p1) << endl;
	cout << t1.contains_edge(test) << endl;

	Point pt(1,1);

	cout << pt_in_tri(pt, t1) << endl;

	Point pt2(0,5);

	cout << pt_in_tri(pt2, t1) << endl;

	Point pt3(1,2);

	cout << pt_in_tri(pt3, t1) << endl;
}
*/