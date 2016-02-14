/*
Implmentation of Poly class.
*/
#include "Poly.h"
#include "ClockwiseComp.h"

#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

Poly::Poly(vector<Edge> &in_edges){
	edges = in_edges;

	for (size_t i = 0; i < edges.size(); i++){
		if(count(verts.begin(), verts.end(), edges[i].p) == 0)
			verts.push_back(edges[i].p);

		if(count(verts.begin(), verts.end(), edges[i].q) == 0)
			verts.push_back(edges[i].q);
	}

	ClockwiseComp comp(Point(0,0));

	sort(verts.begin(), verts.end(), comp);
	sort(edges.begin(), edges.end());

	num_edges = edges.size();
	num_verts = verts.size();
}

bool Poly::contains_edge(Edge &e){
	return count(edges.begin(), edges.end(), e) > 0;
}

float Poly::get_area() const{

	float sum = 0;
	for(size_t v_i = 0; v_i < verts.size(); v_i++){
		Point p1 = verts[v_i];
		Point p2 = verts[(v_i+1) % verts.size()];

		sum += (p1.x*p2.y) - (p1.y*p2.x);
	}

	return sum / float(2);
}

bool Poly::operator<(const Poly& poly) const{
	return get_area() < poly.get_area();
}

bool Poly::contains_vert(Point &p){
	return count(verts.begin(), verts.end(), p) > 0;
}

bool Poly::operator==(const Poly& poly){

	for(size_t i = 0; i < poly.verts.size(); i++){
		if(count(verts.begin(), verts.end(), poly.verts[i]) == 0){
			return false;
		}
	}

	return true;
}

//checks if each point is included exactly twice in edge vector
//TODO doesn't cover all cases
bool Poly::is_valid_poly(){
	map<Point, int> pt_count;

	for(size_t e_i = 0; e_i < edges.size(); e_i++){
		Edge e = edges[e_i];
		
		if(pt_count.count(e.p) == 0){
			pt_count[e.p];
		}

		if(pt_count.count(e.q) == 0){
			pt_count[e.q];
		}

		pt_count[e.q]++;
		pt_count[e.p]++;
	}

	map<Point, int>::iterator map_it;
	for(map_it = pt_count.begin(); map_it != pt_count.end(); map_it++){
		if(map_it->second != 2){
			return false;
		}
	}

	return true;
}

bool Poly::shares_edge(Poly &poly){
	for(size_t i = 0; i < edges.size(); i++){
		if(poly.contains_edge(edges[i])){
			return true;
		}
	}

	return false;
}

bool Poly::shares_vert(Poly &poly){
	for(size_t i = 0; i < verts.size(); i++){
		if(poly.contains_vert(verts[i])){
			return true;
		}
	}

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