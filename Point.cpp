/*
Implementation of the point class.

(c) 2015 Tony Liu.
*/
#include "Point.h"

Point::Point(float xi, float yi){
	 x = xi;
	 y = yi;
}

bool Point::operator<(const Point &p) const{
	return x < p.x;
}

bool Point::operator!=(Point &p){
    return (x != p.x) || (y != p.y);
}

bool Point::operator==(const Point& p) const{
    return (x == p.x) && (y == p.y);
}

