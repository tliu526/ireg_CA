/*
Implementation of the Rule Table class.

(c) 2016 Tony Liu.
*/

#include <iostream>

#include "RuleTable.h"

using namespace std;

RuleTable::RuleTable(Graph<string, Cell>* g, Stencil* s) :
    graph(g),
    stencil(s)
{

}

void RuleTable::transition() {
    cout << "calling base class transition (which does nothing)" << endl;
}

void RuleTable::apply_rule(std::string& label) {

}

void RuleTable::compute_metrics(){
    
}

map<string, Property>* RuleTable::get_metrics() {
    return &metrics;
}

void RuleTable::update_graph(){
    typename map<string, Property>::iterator map_it;
    for(map_it = state_map.begin(); map_it != state_map.end(); map_it++){
        Cell* cell_ptr = graph->get_data(map_it->first);
        Property p = map_it->second;
        cell_ptr->add_property(p);
    }

    state_map.clear();
}

void RuleTable::initialize() {
    stencil->initialize();
}

size_t RuleTable::get_grid_state(){
    return 0;
}