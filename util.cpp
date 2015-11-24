#include "util.h"
	
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
	
vector<Point> generate_uniform_rand(int n, float x, float y) { 
	vector<Point> pts;

	default_random_engine gen;
	uniform_real_distribution<float> x_distr(-x, x);
	uniform_real_distribution<float> y_distr(-y, y);

	for (int i = 0; i < n; i++) {
        pts.push_back(Point(x_distr(gen), y_distr(gen)));
    }

    return pts;
}

int pt_orientation(Point p1, Point p2, Point p3){
    float val = ((p2.y - p1.y) * (p3.x - p2.x)) - ((p3.y - p2.y) * (p2.x - p1.x));

    if (val == 0) 
        return 0;
    
    if (val > 0)  
        return 1;
    else          
        return 2;
}

bool on_segment(Point p1, Point p2, Point p3) {
    if (p2.x <= (max(p1.x, p3.x) && p2.x >= min(p1.x, p3.x)) &&
        p2.y <= (max(p1.y, p3.y) && p2.y >= min(p1.y, p3.y))){
        return true;
    }

    return false;
}

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
    //TODO
}

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

bool pt_in_circumcircle(Point p, Tri &t){
    Point v1 = t.verts[0];
    Point v2 = t.verts[1];
    Point v3 = t.verts[2];
    
    //if points aren't counterclockwise, we make them so by swapping the first two points
    if(pt_orientation(v1,v2,v3) != 2){
        Point temp = v1;
        v1 = v2;
        v2 = temp;
    }

    //calculate the determinant, hard coded three by three
    float a = v1.x - p.x;
    float b = v1.y - p.y;
    float c = (v1.x * v1.x) - (p.x * p.x) + (v1.y * v1.y) - (p.y * p.y);
    float d = v2.x - p.x;
    float e = v2.y - p.y;  
    float f = (v2.x * v2.x) - (p.x * p.x) + (v2.y * v2.y) - (p.y * p.y);
    float g = v3.x - p.x;
    float h = v3.y - p.y;  
    float i = (v3.x * v3.x) - (p.x * p.x) + (v3.y * v3.y) - (p.y * p.y);
    float det = ((a*e*i) + (b*f*g) + (c*d*h) - (c*e*g) - (b*d*i) - (a*f*h));
   // cout << "Det: " << det << endl;
    return det > 0;
}

Point get_circumcenter(Tri &t) {
    Point a = t.verts[0];
    Point b = t.verts[1];
    Point c = t.verts[2];
    
    float D = 2*((a.x*(b.y - c.y)) + (b.x*(c.y - a.y)) + (c.x*(a.y - b.y)));

    float x = ((a.x*a.x + a.y*a.y)*(b.y - c.y) + (b.x*b.x + b.y*b.y)*(c.y - a.y) + (c.x*c.x + c.y*c.y)*(a.y-b.y)) / D;
    float y = ((a.x*a.x + a.y*a.y)*(c.x - b.x) + (b.x*b.x + b.y*b.y)*(a.x - c.x) + (c.x*c.x + c.y*c.y)*(b.x-a.x)) / D;

    return Point(x,y);
}

//ax + b
pair<float, float> get_line(Point p1, Point p2) {
    float a, b; 

    a = (p2.y - p1.y) / (p2.x - p1.x);
    b = p1.y - (a*p1.x);

    return pair<float,float>(a,b);
}

int num_digits(int n){
    int n_digits = 0;

    while (n/=10){
        n_digits++;
    }

    return n_digits;
}

int digit_diff(int n, int m){
    return num_digits(m) - num_digits(n);
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