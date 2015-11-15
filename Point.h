/*
An implementation of points, currently using integer coordinates.

(c) 2015 Tony Liu.
*/
#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{
public:
    int x;
    int y;

    Point() {}

    Point(int xi, int yi);

    bool operator!=(Point &p);
    bool operator==(const Point &p);

	//toString equivalent
    friend std::ostream & operator<<(std::ostream & _stream, Point const &p){
    	_stream << "(" << p.x << ", " << p.y << ")";
        return _stream;
    }
};

#endif