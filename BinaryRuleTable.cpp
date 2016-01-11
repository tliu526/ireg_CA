/**
Implementation of BinaryRuleTable.

(c) 2016 Tony Liu.
*/

#include "BinaryRuleTable.h"

const string BinaryRuleTable::PERCENT_ON = "PercentOn";
const string BinaryRuleTable::INIT_PERCENT = "InitPercent";

BinaryRuleTable::BinaryRuleTable(Graph<std::string,Cell>* graph, float percent_on, float s) : 
    RuleTable(graph)
{
    init_percent_on = percent_on;
    seed = s;
    type = OTHER;
    radius = -1;
}

int BinaryRuleTable::get_on_count() {
    vector<string> labels = graph->get_vert_labels();
    int on_cells = 0;
    for(size_t i = 0; i < labels.size(); i++){
        Property p = graph->get_data(labels[i])->get_property(B_STATE);
        
        if(p.get_type() == Property::BOOL && p.b){
            on_cells++;
        }
    }

    return on_cells;
}

size_t BinaryRuleTable::get_grid_state(){
    //TODO optimize get_vert_labels() and ensure consistency
    vector<string> vert_labels = graph->get_vert_labels();

    vector<bool> b_vec;

    for (size_t i = 0; i < vert_labels.size(); i++){
        Property p = graph->get_data(vert_labels[i])->get_property(B_STATE);
        if(p.get_type() == Property::BOOL){
            b_vec.push_back(p.b);
        }
    }

    hash<vector<bool>> hash_fn;

    return hash_fn(b_vec);
}

void BinaryRuleTable::transition() {}
void BinaryRuleTable::initialize() {}
void BinaryRuleTable::compute_metrics() {}
void BinaryRuleTable::apply_rule(string& l) {}