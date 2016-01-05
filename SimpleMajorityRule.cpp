/*
Implementation of SimpleMajorityRule.

(c) 2016 Tony Liu.
*/

#include "SimpleMajorityRule.h"

using namespace std;

SimpleMajorityRule::SimpleMajorityRule() {
    rule_type = OTHER;
    radius = 0;
}
    
void SimpleMajorityRule::transition(Graph<std::string,Cell>* graph){
    //write current state to state_history

    //iterate over all cells in a consistent order, calling apply_rule on each cell
    //for all cells (label):
    //  apply_rule(label)
}

void SimpleMajorityRule::apply_rule(std::string label, Graph<std::string,Cell>* graph){

    std::list<std::string>* neighbors = graph->get_neighbors(label);

    //for all neighbors:
    //check state of the neighbors in state_history
    //set state of current cell
}