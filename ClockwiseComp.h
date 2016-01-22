/**
A functor that implements a clockwise point comparator around an anchor point.

(c) 2016 Tony Liu.
*/

#ifndef CLOCKWISECOMP_H
#define CLOCKWISECOMP_H

#include "Point.h"

class ClockwiseComp {
    public:
        ClockwiseComp(Point p) : pt(p) {};

        /**
        sorts points clockwise, with pt as the anchor point.
        From: http://stackoverflow.com/questions/6989100/sort-points-in-clockwise-order
        */
        bool operator()(const Point &p1, const Point &p2) {
            if (p1.x - pt.x >= 0 && p2.x - pt.x < 0)
                return true;
            if (p1.x - pt.x < 0 && p2.x - pt.x >= 0)
                return false;
            if (p1.x - pt.x == 0 && p2.x - pt.x == 0) {
                if (p1.y - pt.y >= 0 || p2.y - pt.y >= 0)
                    return p1.y > p2.y;
                return p2.y > p1.y;
            }

            // compute the cross product of vectors (center -> p1) x (center -> p2)
            float det = (p1.x - pt.x) * (p2.y - pt.y) - (p2.x - pt.x) * (p1.y - pt.y);
            if (det < 0)
                return true;
            if (det > 0)
                return false;

            // points a and p2 are on the same line from the center
            // check which point is closer to the center
            float d1 = (p1.x - pt.x) * (p1.x - pt.x) + (p1.y - pt.y) * (p1.y - pt.y);
            float d2 = (p2.x - pt.x) * (p2.x - pt.x) + (p2.y - pt.y) * (p2.y - pt.y);
            return d1 > d2;
        }

    private:
        Point pt;
};

#endif