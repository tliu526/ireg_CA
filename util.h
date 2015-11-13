/*
Contains various utilities, incluing random point generating functions.

Issues to be resolved:
- How do we scale up if we want to expand the grid?
- floating point precision?

Current methods for generating points:
- uniform random
- Poisson disk sampling


(c) Tony Liu 2015.
*/

#ifndef UTIL_H
#define UTIL_H 

#include <utility>
#include <vector>
#include <string>

struct point{
    float x;
    float y;

    point(float xi, float yi){
        x = xi;
        y = yi;
    }
};

struct edge{
    point p1;
    point p2;

    edge(point one, point two){
        p1 = one;
        p2 = two;
    }
};

//TODO do we want this?
class PointGenerator {
public:
	virtual void generate_points(int n, float x, float y) = 0; //must be overidden
	
	void pts_to_file(std::string f); //writes points to file

protected:
	int n;
	float x; // width of grid plane
	float y; // height of grid plane
	std::vector<point> pts;
};

/*
Populates pts vector with n points sampled uniformly in a x by y dimension space.
*/
void generate_uniform_rand(std::vector<point>& pts, int n, float x, float y);

/*
Populates pts vector with n points from a poisson disk in a x by y dimension space.
*/
void generate_poisson_disk(std::vector<point>& pts, int n, float x, float y);

/*
Writes all points to file f
*/
void pts_to_file(std::vector<point>& pts, std::string f); 

/*
Checks whether the two edges intersect
*/
bool edge_intersect(edge e1, edge e2) {
    //TODO
}
#endif