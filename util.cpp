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

/*
	void generate_poisson_disk(vector<point>& pts, int n, float x, float y, float r){

}

//TODO defining the dimensions?
void pts_to_file(vector<point>& pts, string f){

} 

//For debugging my incompetence in C++
int main() {
	vector<point> points;
	generate_uniform_rand(points, 10, 10.0f, 10.0f);

	for (int i = 0; i < points.size(); i++){
		cout << points[i].x << "," << points[i].y << "\n";
	}

	return 0;
}
n*/