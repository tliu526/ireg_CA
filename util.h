/*
Contains various utilities, incluing random point generating functions.

Issues to be resolved:
- How do we scale up if we want to expand the grid?
- floating point precision?

Current methods for generating points:
- uniform random
- Poisson disk sampling

TODO: do we want integer coordinates or floating point coordinates?
(c) Tony Liu 2015.
*/

#ifndef UTIL_H
#define UTIL_H 

#include "Tri.h"
#include "Edge.h"

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <random>

inline int max(int a, int b){ return (a<b) ? b : a; }
inline int min(int a, int b){ return (a>b) ? b : a; }

/**** POINT GENERATION ****/

/*
Populates pts vector with n points sampled uniformly in a 2x by 2y dimension space.
*/
std::vector<Point> generate_uniform_rand(int n, float x, float y);

/*
Populates pts vector with n points from a poisson disk in a x by y dimension space.
*/
void generate_poisson_disk(std::vector<Point>& pts, int n, float x, float y);


/**** GEOMETRY FUNCTIONS ****/

/*
Determines the orientation of the two points.
From http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
@return: 0 if collinear, 1 if clockwise, 2 if counterclockwise
*/
int pt_orientation(Point p1, Point p2, Point p3);

/*
Checks whether p2 is on the line segment p1p3.
*/
bool on_segment(Point p1, Point p2, Point p3);

/*
Checks whether the two edges intersect. Utilizes on_segment and pt_orientation.
*/
bool edge_intersect(Edge e1, Edge e2);

/*
Checks whether p is enclosed within the boundary of t. Uses the barycentric method.
From http://totologic.blogspot.fr/2014/01/accurate-point-in-triangle-test.html
*/
bool pt_in_tri(Point p, Tri& t);

/*
checks whether Point p is in the circumcircle defined by t.
TODO: what about points lying directly on the circumcircle?
*/
bool pt_in_circumcircle(Point p, Tri& t);

/**** LINEAR ALG FUNCTIONS ****/


/**** MISC ****/
/*
Returns the difference in digits between n and m, where n < m. Useful for pretty printing.
*/
int digit_diff(int n, int m);

/*
Returns the number of digits in n, useful for pretty printing.
*/
int num_digits(int n);
#endif