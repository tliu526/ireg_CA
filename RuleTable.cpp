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

// For testing speed of spreading activation
//    cells_to_update.clear();

    typename map<string, Property>::iterator map_it;
    for(map_it = state_map.begin(); map_it != state_map.end(); map_it++){
        string cell_label = map_it->first;
        Cell* cell_ptr = graph->get_data(cell_label);
        Property p = map_it->second;
        
        cell_ptr->add_property(p);

/*
        //only update if the state is different
        if(cell_ptr->get_property(p.get_label()) != p){
            cell_ptr->add_property(p);
            add_cells(cell_label);
        }
*/
    }

    state_map.clear();
}

void RuleTable::add_cells(string &label){
    vector<string> potential_cells;

    potential_cells.push_back(label);                


    /*
    //grab neighbors and neighbor's neighbors
    list<string>* neighbors = graph->get_neighbors(label);
    typename list<string>::iterator list_it;
    for(list_it = neighbors->begin(); list_it != neighbors->end(); list_it++) {
        potential_cells.push_back(*list_it);
        list<string>* n_neighbors = graph->get_neighbors(*list_it);
        potential_cells.insert(potential_cells.end(), n_neighbors->begin(), n_neighbors->end());
    }
    */

    list<string>* neighbors = graph->get_neighbors(label);
    potential_cells.insert(potential_cells.end(), neighbors->begin(), neighbors->end());

    //add unique labels to cells_to_update
    for(size_t i = 0; i < potential_cells.size(); i++){
        if(count(cells_to_update.begin(),cells_to_update.end(), potential_cells[i]) == 0){
            cells_to_update.push_back(potential_cells[i]);
        }
    }
}

void RuleTable::initialize() {
    cells_to_update = graph->get_vert_labels();
    //stencil->initialize();
}

size_t RuleTable::get_grid_state(){
    return 0;
}
