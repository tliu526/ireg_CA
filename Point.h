/*
An implementation of points, currently using integer coordinates.

(c) 2015 Tony Liu.
*/
#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point{
public:
    float x;
    float y;

    Point() {}

    Point(float xi, float yi);

    bool operator!=(Point &p);
    bool operator==(const Point &p) const;
    bool operator<(const Point &p) const;
	//toString equivalent
    friend std::ostream & operator<<(std::ostream & _stream, Point const &p){
    	_stream << "(" << p.x << "," << p.y << ")";
        return _stream;
    }
};

#endif