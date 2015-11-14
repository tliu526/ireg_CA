#include "Edge.h"

Edge::Edge(Point one, Point two){
        p = one;
        q = two;
    }

bool Edge::operator==(const Edge &e){
    return ((p == e.p) && (q == e.q)) || ((p == e.q) && (q == e.p));
}
