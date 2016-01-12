/**
An implementation of directly translated GoL rules.

(c) 2016 Tony Liu.
*/

#include "SimpleLifeRule.h"

using namespace std;

SimpleLifeRule::SimpleLifeRule(Graph<string, Cell>* graph, float percent_on, float s) 
    : BinaryRuleTable(graph, percent_on, s) {}

SimpleLifeRule::SimpleLifeRule(Graph<std::string,Cell>* graph, float init_percent, float seed, Stencil& stencil) 
  : BinaryRuleTable(graph, init_percent, seed, stencil) {}

void SimpleLifeRule::initialize() {
    BinaryRuleTable::initialize();
}

void SimpleLifeRule::compute_metrics() {
    float percentage = float(get_on_count()) / float(num_cells);
    metrics[PERCENT_ON].set_float(percentage);
}


void SimpleLifeRule::transition() {
    BinaryRuleTable::transition();
}

void SimpleLifeRule::apply_rule(string &label) {
    int count = get_on_count(label);
    Property p = graph->get_data(label)->get_property(B_STATE);
    bool cell_state;
    
    if(p.get_type() == Property::BOOL){
        cell_state = p.b;
    }
    else {
        cout << "Invalid State type" << endl;
        return;
    }

    if(cell_state) {
        if(count < 2 || count > 3){
            p.set_bool(false);
            state_map[label] = p;
        }
    }
    else if(count == 3){
        p.set_bool(true);
        state_map[label] = p;
    }
}  