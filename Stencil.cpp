/*
Implementation of Stencils.

(c) 2016 Tony Liu.
*/

#include "Stencil.h"

using namespace std;

Stencil::Stencil(Graph<std::string, Cell>* g) :
    graph(g)
{
    type = OTHER;
    initialize();
}

//defaults to mapping cells to adjacent neighbors
void Stencil::initialize() {
    cout << "Stencil init" << endl;

    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        //copy the list over
        list<string> *neighbors = graph->get_neighbors(labels[i]);
        neighbor_map[labels[i]] = vector<string> {begin(*neighbors), end(*neighbors)};
    }
}

vector<string>* Stencil::get_neighbors(string& label){
    if(neighbor_map.count(label) != 0){
        return &neighbor_map[label];
    }

    return NULL;
}