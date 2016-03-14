#include "util.h"
	
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <climits>

using namespace std;

vector<Point> generate_uniform_rand(int n, float x, float y, float seed) { 
	vector<Point> pts;

	default_random_engine gen;
    gen.seed(seed);

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

bool edge_intersect(Edge &e1, Edge &e2) {
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

//k is limit of rejection sample size, using algorithm from br07
//pre: pts is empty
vector<Point> generate_poisson_disk(float x, float y, int k, float r, float seed){
    vector<Point> pts;

    float cell_size = r / sqrt(2);

    int w = (int)ceil(x / cell_size);
    int h = (int)ceil(y / cell_size);

    //init grid to -1
    vector<vector<int>> grid(w);
    for (int i = 0; i < grid.size(); i++){
        grid[i] = vector<int>(h, -1);
    }
 
    vector<Point> active;

    default_random_engine gen;
    gen.seed(seed);
    uniform_real_distribution<float> x_distr(0, x);
    uniform_real_distribution<float> y_distr(0, y);

    Point first(x_distr(gen), y_distr(gen));

    active.push_back(first);

    while(active.size() > 0){

        random_shuffle(active.begin(), active.end());
        
        Point p = active[active.size()-1];
        active.pop_back();

        for(int i = 0; i < k; i++){
            Point sample = generate_annulus_pt(p, r);

            if((sample.x > 0) && (sample.x < x) && (sample.y > 0) && (sample.y < y)){
                if(check_neighborhood(sample, grid, r, pts, cell_size)){
                    int sample_w = (int)(sample.x / cell_size);
                    int sample_h = (int)(sample.y / cell_size);

                    pts.push_back(sample);
                    grid[sample_w][sample_h] = (find(pts.begin(), pts.end(), sample) - pts.begin());
                    active.push_back(sample);
                }
            }

        }
    }

    cout << "Number of points: " << pts.size() << endl;
    return pts;
}

bool check_neighborhood(Point p, vector<vector<int>> &grid, float min_dist, vector<Point> &pts, float cell_size){
    int sample_w = (int)(p.x / cell_size);
    int sample_h = (int)(p.y / cell_size);

    //need to check the 5x5 neighborhood around the point
    int w_begin = max(0, sample_w-2);
    int w_end = min(sample_w + 3, grid.size());
    int h_begin = max(0, sample_h-2);
    int h_end = min(sample_h + 3, grid[0].size());

    for(int i = w_begin; i < w_end; i++){
        for(int j = h_begin; j < h_end; j++){
            if((grid[i][j] != -1) && (distance(p, pts[grid[i][j]]) < min_dist)) {
                return false;
            }
        }
    }                

    return true;
}

Point generate_annulus_pt(Point p, float min_dist){

    float rand_angle = 2 * 4*atan(1) * (rand() / float(RAND_MAX));
    float rand_rad = min_dist * ((rand()/ float(RAND_MAX)) + 1); //in between min_dist and 2 * min_dist

    float x = p.x + rand_rad * cos(rand_angle); 
    float y = p.y + rand_rad * sin(rand_angle); 

    return Point(x,y);
}

float distance(const Point &p1, const Point &p2){
    float x = p2.x - p1.x;
    float y = p2.y - p1.y;

    return sqrt((x*x) + (y*y));
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

bool pt_in_circle(Point &center, Point &p, float radius) {
    float diff = ((p.x - center.x) * (p.x - center.x)) + ((p.y - center.y) * (p.y - center.y));
    return diff <= radius * radius;
}

vector<Point> generate_from_file(string f){
    istringstream iss;
    vector<Point> pts;
    string line;
    float x,y;
    ifstream in(f);
    
    while(getline(in, line)){
        iss.str(line);
        iss.clear();
        iss >> x >> y;
    
        Point p(x,y);
        pts.push_back(p);
    }

    return pts;
}

int count_bits(int n){
    int count = 0;
    while(n > 0){
        n >>= 1;
        count++;
    }

    return count;
}

string get_bit_str(int n) {
    string bit_str = "";

    while(n > 0){
        bit_str = to_string((n & 1)) + bit_str;
        n >>= 1;
    }

    return bit_str;
}

string str_change_base(int n, int b) {
    int rmdr; //remainder
    string outstr;
    while(n) {
        rmdr = n % b;
        outstr = to_string(rmdr) + outstr;
        n /= b;
    }

    return outstr;
}

Point midpoint(Edge &e){
    float x = (float(e.p.x) + float(e.q.x)) / float(2);
    float y = (float(e.p.y) + float(e.q.y)) / float(2);

    return Point(x,y);
}

//NOTE: does not handle the case of pt laying on an edge
//Assumes convex, if point is in poly there will be exactly one intersectoin
bool pt_in_poly(Point &pt, Poly& poly) {
    Point inf_pt(INT_MAX, pt.y);
  //  cout << inf_pt << endl;
    Edge test(pt, inf_pt);
    int intersect_count = 0;

    for (size_t e_i = 0; e_i < poly.edges.size(); e_i++){
        if(edge_intersect(test, poly.edges[e_i])){
    //        cout << "intersect" << endl;
            intersect_count++;
        }
    }

    return intersect_count == 1;
}

/*
//For debugging my incompetence in C++
int main() {
    //TODO debugggggg
    Point p1(-0.5,-0.5);
    Point p2(1,-1);
    Point p3(-1,-1);
    Point p4(0,1);

    vector<Edge> edges;
    edges.push_back(Edge(p2,p3));
    edges.push_back(Edge(p2,p4));
    edges.push_back(Edge(p3,p4));

    Poly poly(edges);

    cout <<  p1 << " in Poly: " << pt_in_poly(p1, poly) << endl;

	return 0;
}
*/