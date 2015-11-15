#include "Edge.h"

Edge::Edge(Point one, Point two){
        p = one;
        q = two;
    }

bool Edge::operator==(const Edge &e){
    return ((p == e.p) && (q == e.q)) || ((p == e.q) && (q == e.p));
}

bool Edge::operator!=(Edge &e){
	return !(*this == e);
}

bool Edge::contains(Point pt){
	return (p == pt) || (q == pt);
}
