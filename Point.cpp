/*
Implementation of the point class.

(c) 2015 Tony Liu.
*/
#include "Point.h"

Point::Point(int xi, int yi){
	 x = xi;
	 y = yi;
}

bool Point::operator!=(Point &p){
    return (x != p.x) || (y != p.y);
}

bool Point::operator==(const Point& p){
    return (x == p.x) && (y == p.y);
}

