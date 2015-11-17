#include "Edge.h"

Edge::Edge(Point one, Point two){
	if (one < two){
        p = one;
        q = two;
    }
    else {
    	p = two;
    	q = one;
    }
}

bool Edge::operator==(const Edge &e){
    return ((p == e.p) && (q == e.q)) || ((p == e.q) && (q == e.p));
}

bool Edge::operator!=(Edge &e){
	return !(*this == e);
}

bool Edge::operator< (const Edge &e) const{
	if(p == e.p){
		return q < e.q;
	}
	return p < e.p;
}

bool Edge::contains(Point pt){
	return (p == pt) || (q == pt);
}
