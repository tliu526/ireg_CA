/**
A functor that implements a distance from anchor point comparator.

(c) 2016 Tony Liu.
*/

#ifndef DISTCOMP_H
#define DISTCOMP_H

#include "Point.h"
#include "util.h"

class DistComp {
    public:
        DistComp(Point p) : pt(p) {};

    bool operator()(const Point &p1, const Point &p2){
        return distance(pt, p1) < distance(pt, p2);
    }

    private:
        Point pt;
};

#endif