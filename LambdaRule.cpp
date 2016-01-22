/**
Implementation of the LambdaRule.

(c) 2016 Tony Liu.
*/

#include "LambdaRule.h"

#include <string>

using namespace std;

void LambdaRule::initialize() {
    RuleTable::initialize();


}

size_t LambdaRule::get_grid_state() {
    //TODO optimize get_vert_labels() and ensure consistency
    vector<string> vert_labels = graph->get_vert_labels();

    string state = "";

    for (size_t i = 0; i < vert_labels.size(); i++){
        Property p = graph->get_data(vert_labels[i])->get_property(GridGenerator::I_STATE);
        if(p.get_type() == Property::INT){
            state += to_string(p.i);
        }
    }

    hash<string> hash_fn;

    return hash_fn(state);
}

