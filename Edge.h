/*
An implementation of Edges.

(c) 2015 Tony Liu.
*/

#ifndef EDGE_H
#define EDGE_H

#include "Point.h"

#include <iostream>

class Edge{
public:
    Point p;
    Point q;

    Edge() {}

    Edge(Point one, Point two);

    bool operator!=(Edge &e);    
    bool operator== (const Edge &e);
    bool operator< (const Edge &e) const;
    bool contains (Point p);

    friend std::ostream & operator<<(std::ostream & _stream, Edge const &e){
        _stream << e.p << ", " << e.q;

        return _stream;
    }
};

#endif