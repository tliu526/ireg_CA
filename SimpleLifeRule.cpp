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
    //TODO
}

void apply_rule(string &label) {
    //TODO
}  
