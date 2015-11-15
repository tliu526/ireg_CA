#include "util.h"
	
#include <random>
#include <iostream>
#include <vector>

using namespace std;
	
vector<Point> generate_uniform_rand(int n, int x, int y) { 
	vector<Point> pts;

	default_random_engine gen;
	uniform_int_distribution<int> x_distr(-x, x);
	uniform_int_distribution<int> y_distr(-y, y);

	for (int i = 0; i < n; i++) {
        pts.push_back(Point(x_distr(gen), y_distr(gen)));
    }

    return pts;
}

/*
Returns the orientation of the two points
From http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
@return: 0 if collinear, 1 if clockwise, 2 if counterclockwise
*/
int pt_orientation(Point p1, Point p2, Point p3){
    int val = ((p2.y - p1.y) * (p3.x - p2.x)) - ((p3.y - p2.y) * (p2.x - p1.x));

    if (val == 0) 
        return 0;
    
    if (val > 0)  
        return 1;
    else          
        return 2;
}

/*
Checks whether p2 is on the line segment p1p3
*/
bool on_segment(Point p1, Point p2, Point p3) {
    if (p2.x <= (max(p1.x, p3.x) && p2.x >= min(p1.x, p3.x)) &&
        p2.y <= (max(p1.y, p3.y) && p2.y >= min(p1.y, p3.y))){
        return true;
    }

    return false;
}

/*
Checks whether the two edges intersect
@return: whether e1 and e2 intersect
*/
bool edge_intersect(Edge e1, Edge e2) {
    int o1 = pt_orientation(e1.p, e1.q, e2.p);
    int o2 = pt_orientation(e1.p, e1.q, e2.q);
    int o3 = pt_orientation(e2.p, e2.q, e1.p);
    int o4 = pt_orientation(e2.p, e2.q, e1.q);

    if (o1 != o2 && o3 != o4)
        return true;
    
    if (o1 == 0 && on_segment(e1.p, e2.p, e1.q)) 
        return true;
    if (o2 == 0 && on_segment(e1.p, e2.q, e1.q)) 
        return true;
    if (o3 == 0 && on_segment(e2.p, e1.p, e2.q)) 
        return true;
    if (o4 == 0 && on_segment(e2.p, e1.q, e2.q)) 
        return true;

    return false;
}


void generate_poisson_disk(vector<Point>& pts, int n, float x, float y, float r){

}

//TODO defining the dimensions?
void pts_to_file(vector<Point>& pts, string f){

}  

//Using barycentric coordinate system
//http://totologic.blogspot.fr/2014/01/accurate-point-in-triangle-test.html
bool pt_in_tri(Point pt, Tri& tri){
    Point v1 = tri.verts[0];
    Point v2 = tri.verts[1];
    Point v3 = tri.verts[2];

    float denom = (v2.y - v3.y)*(v1.x - v3.x) + (v3.x - v2.x)*(v1.y - v3.y);
    float a = ((v2.y - v3.y)*(pt.x - v3.x) + (v3.x - v2.x)*(pt.y - v3.y)) / denom;
    float b = ((v3.y - v1.y)*(pt.x - v3.x) + (v1.x - v3.x)*(pt.y - v3.y)) / denom;
    float c = 1 - a - b;

    //cout << a << endl;
    //cout << b << endl;
    //cout << c << endl;

    return (0 <= a) && (a <= 1) && (0 <= b) && (b <= 1) && (0 <= c) && (c <= 1);
}

/*
//For debugging my incompetence in C++
int main() {
	vector<point> points;
	generate_uniform_rand(points, 10, 10.0f, 10.0f);

	for (int i = 0; i < points.size(); i++){
		cout << points[i].x << "," << points[i].y << "\n";
	}

	return 0;
}
*/