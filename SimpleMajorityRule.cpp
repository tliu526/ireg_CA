/*
Implementation of SimpleMajorityRule.

(c) 2016 Tony Liu.
*/

#include "SimpleMajorityRule.h"

using namespace std;

SimpleMajorityRule::SimpleMajorityRule(Graph<string, Cell>* graph, Stencil* stencil, int percent_on, float s, int noise) 
    : MajorityRule(graph, stencil, percent_on, s, noise) {}

//only looks for B_STATE
void SimpleMajorityRule::apply_rule(std::string& vert_label){
    vector<string>* neighbors = stencil->get_neighbors(vert_label);
    Property p = graph->get_data(vert_label)->get_property(GridGenerator::B_STATE);
    int count = get_on_count(vert_label);
    int neighborhood_size = neighbors->size() + 1;

    if(p.get_type() == Property::BOOL){
        if(p.b){
            count++;
        }
    }
    else {
        cout << "Invalid State type" << endl;
        return;
    }

    //change to majority value of its neighbors. If no majority, keep the same state
    if (float(count) > (float(neighborhood_size)/float(2))) {
        p.set_bool(true);
        state_map[vert_label] = p;
    }
    else if (float(count) < (float(neighborhood_size)/float(2))){
        p.set_bool(false);
        state_map[vert_label] = p;
    }
    //if count is equal to half of neighborhood size, nothing happens
}
