/*
Contains various utilities, incluing random point generating functions.

Issues to be resolved:
- How do we scale up if we want to expand the grid?
- floating point precision?
- Since this does not encapsulate a class, should we move this to a utils method?

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

using namespace std;

typedef pair<float, float> point; // (x,y)

//TODO do we want this?
class PointGenerator {
public:
	virtual void generate_points(int n, float x, float y) = 0; //must be overidden
	
	void pts_to_file(string f); //writes points to file

protected:
	int n;
	float x; // width of grid plane
	float y; // height of grid plane
	vector<point> pts;
};

/*
Populates pts vector with n points sampled uniformly in a x by y dimension space.
*/
void generate_uniform_rand(vector<point>& pts, int n, float x, float y);

/*
Populates pts vector with n points from a poisson disk in a x by y dimension space.
*/
void generate_poisson_disk(vector<point>& pts, int n, float x, float y);

/*
Writes all points to file f
*/
void pts_to_file(vector<point>& pts, string f); 

#endif