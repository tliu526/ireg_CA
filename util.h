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

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <random>

inline int max(int a, int b){ return (a<b) ? b : a; }
inline int min(int a, int b){ return (a>b) ? b : a; }

struct Point{
    int x;
    int y;

    Point() {}

    Point(int xi, int yi){
        x = xi;
        y = yi;
    }

    bool equals(Point p){
        return (x == p.x) && (y == p.y);
    }

    //toString equivalent
    friend std::ostream & operator<<(std::ostream & _stream, Point const &p){
        _stream << "(" << p.x << ", " << p.y << ")";
    }
};

struct Edge{
    Point p;
    Point q;

    Edge() {}

    Edge(Point one, Point two){
        p = one;
        q = two;
    }

  friend std::ostream & operator<<(std::ostream & _stream, Edge const &e){
        _stream << e.p << ", " << e.q;
    }
};

/*
Populates pts vector with n points sampled uniformly in a 2x by 2y dimension space.
*/
std::vector<Point> generate_uniform_rand(int n, int x, int y);

/*
Populates pts vector with n points from a poisson disk in a x by y dimension space.
*/
void generate_poisson_disk(std::vector<Point>& pts, int n, float x, float y);

/*
Writes all points to file f
*/
void pts_to_file(std::vector<Point>& pts, std::string f); 

/**** GEOMETRY FUNCTIONS ****/

int pt_orientation(Point p1, Point p2, Point p3);

bool on_segment(Point p1, Point p2, Point p3);

bool edge_intersect(Edge e1, Edge e2);

#endif