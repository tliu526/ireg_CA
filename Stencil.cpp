/*
Implementation of Stencils.

(c) 2016 Tony Liu.
*/

#include "Stencil.h"

using namespace std;

Stencil::Stencil() {
    type = OTHER;
}

//defaults to mapping cells to adjacent neighbors
void Stencil::initialize(Graph<string, Cell>* graph) {
    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        //copy the list over
        list<string> *neighbors = graph->get_neighbors(labels[i]);
        neighbor_map[labels[i]] = vector<string> {begin(*neighbors), end(*neighbors)};
    }
}