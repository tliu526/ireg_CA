/*
Implementation of SimpleMajorityRule.

(c) 2016 Tony Liu.
*/

#include "SimpleMajorityRule.h"

using namespace std;

SimpleMajorityRule::SimpleMajorityRule(Graph<string, Cell>* graph) 
    : RuleTable(graph)
{
    type = OTHER;
    radius = 0;
}

//TODO write current state to state_history    
void SimpleMajorityRule::transition(){
    vector<string> labels = graph->get_vert_labels();

    int on_cells = 0;
    for(size_t i = 0; i < labels.size(); i++){
        Property p = graph->get_data(labels[i])->get_property(B_STATE);
        
        if(p.get_type() == Property::BOOL && p.b){
            on_cells++;
        }

        apply_rule(labels[i]);
    }

    cout << "Number of on cells:" << " " << on_cells << endl;

    update_graph();
}

//only looks for B_STATE
void SimpleMajorityRule::apply_rule(std::string& vert_label){
    vector<string>* neighbors = stencil.get_neighbors(vert_label);
    Property p;

    int count = 0;
    for(size_t i = 0 ; i < neighbors->size(); i++){
        p = graph->get_data((*neighbors)[i])->get_property(B_STATE);
        
        if(p.get_type() == Property::BOOL){
            if(p.b){
                count++;
            }            
        }
        else {
            cout << "Invalid State type" << endl;
            return;
        }
        
    }

    //switch to majority value of its neighbors
    if (count > (neighbors->size()/2)) {
        p.set_bool(true);
    }

    else {
        p.set_bool(false);
    }

    state_map[vert_label] = p;
}