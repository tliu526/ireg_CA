/*
Implementation of the Rule Table class.

(c) 2016 Tony Liu.
*/

#include <iostream>

#include "RuleTable.h"
#include "DistComp.h"

using namespace std;

RuleTable::RuleTable(Graph<string, Cell>* g, Stencil* s) :
    graph(g),
    stencil(s)
{

}

void RuleTable::transition() {
    //vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < cells_to_update.size(); i++){
        apply_rule(cells_to_update[i]);
    }

    //cout << "Number of on cells:" << " " << get_on_count() << endl;

    update_graph();
}

void RuleTable::apply_rule(std::string& label) {
    cout << "calling base class apply_rule (which does nothing)" << endl;
}

void RuleTable::compute_metrics(){
    
}

map<string, Property>* RuleTable::get_metrics() {
    return &metrics;
}

void RuleTable::update_graph(){
    cells_to_update.clear();

    typename map<string, Property>::iterator map_it;
    for(map_it = state_map.begin(); map_it != state_map.end(); map_it++){
        string cell_label = map_it->first;
        Cell* cell_ptr = graph->get_data(cell_label);
        Property p = map_it->second;

        //only update if the state is different
        if(cell_ptr->get_property(p.get_label()) != p){
            cell_ptr->add_property(p);
            cells_to_update.push_back(cell_label);
            list<string>* neighbors = graph->get_neighbors(cell_label);
            cells_to_update.insert(cells_to_update.end(), neighbors->begin(), neighbors->end());
        }

    }

    state_map.clear();
}

void RuleTable::initialize() {
    cells_to_update = graph->get_vert_labels();
    //stencil->initialize();
}

size_t RuleTable::get_grid_state(){
    return 0;
}