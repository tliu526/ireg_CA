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

#include "Tri.h"
#include "Edge.h"
#include "Poly.h"

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <bitset>

inline int max(int a, int b){ return (a<b) ? b : a; }
inline int min(int a, int b){ return (a>b) ? b : a; }

/**** POINT GENERATION ****/

/*
Populates pts vector with n points sampled uniformly in a 2x by 2y space. Uses a seed.
*/
std::vector<Point> generate_uniform_rand(int n, float x, float y, float seed);

/*
Populates pts vector with points from a poisson disk distribution (2x by 2y) with radius r.
From http://devmag.org.za/2009/05/03/poisson-disk-sampling/, br07. Uses a seed.
*/
std::vector<Point> generate_poisson_disk(float x, float y, int n, float r, float seed);

/*
generates a point uniformly from within the minDist, 2*minDist annulus
*/
Point generate_annulus_pt(Point p, float minDist);

/*
Helper for poisson disk. Checks if a point p has 
*/
bool check_neighborhood(Point p, std::vector<std::vector<int> >&grid, float min_dist, std::vector<Point> &pts, float cell_size);

/**
Reads from a input file to populate vector.
The input file will be in the following format: x y 
*/
std::vector<Point> generate_from_file(std::string file);

/**** GEOMETRY FUNCTIONS ****/
/**
Returns the midpoint of the points in the edge
*/
Point midpoint(Edge& e);

/*
Gives the distance between two points
*/
float distance(const Point &p1, const Point &p2);

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
bool edge_intersect(Edge &e1, Edge &e2);

/*
Checks whether p is enclosed within the boundary of t. Uses the barycentric method.
From http://totologic.blogspot.fr/2014/01/accurate-point-in-triangle-test.html
*/
bool pt_in_tri(Point p, Tri& t);

/*
Checks whether the pt is enclosed within the boundary of poly. Uses the 
*/
bool pt_in_poly(Point &pt, Poly& poly);

/*
checks whether Point p is in the circumcircle defined by t.
TODO: what about points lying directly on the circumcircle?
*/
bool pt_in_circumcircle(Point p, Tri& t);

/**
Checks whether Point p is in the circle defined by center and radius.
*/
bool pt_in_circle(Point &center, Point& p, float radius);

/*
Gets the circumcenter of a tri. The circumcenter of a tri in a Delaunay triangulation
is a vertex in the Voronoi diagram.
From https://en.wikipedia.org/wiki/Circumscribed_circle#Cartesian_coordinates_2
*/
Point get_circumcenter(Tri &t);

/*
Returns the (slope, intercept) of the line given by p1 and p2.
*/
std::pair<float,float> get_line(Point p1, Point p2);

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

/**
Counts the number of bits in integer n
*/
int count_bits(int n);


/**
Returns the bitstring representation of n
*/
std::string get_bit_str(int n);

/**
Returns the string representation of n in base b
*/
std::string str_change_base(int n, int b);
#endif