/*
Implementation of MajorityRule.

(c) 2016 Tony Liu.
*/

#include "MajorityRule.h"

using namespace std;

const string MajorityRule::CORRECT_CLASS = "CorrectClass";

MajorityRule::MajorityRule(Graph<string, Cell>* graph, Stencil* stencil, int percent_on, float s) 
    : BinaryRuleTable(graph, stencil, percent_on, s) {}

void MajorityRule::initialize() {
    BinaryRuleTable::initialize();

    //initialize metrics 
    Property correct_class(CORRECT_CLASS, false);
    metrics[CORRECT_CLASS] = correct_class;

    target_class = (float(get_on_count()) / float(num_cells)) > 0.5;
}

void MajorityRule::compute_metrics() {
    float percentage = float(get_on_count()) / float(num_cells);
    if(get_on_count() == num_cells){
        //currently have all ON cells
        metrics[CORRECT_CLASS].set_bool(target_class);    
    }
    else if(get_on_count() == 0){
        //currently have all OFF cells
        metrics[CORRECT_CLASS].set_bool(!target_class);
    }
    else {
        //we have incorrect classification
        metrics[CORRECT_CLASS].set_bool(false);
    }

    metrics[PERCENT_ON].set_float(percentage);

    //cout << "Correct Classification: " << metrics[CORRECT_CLASS].to_string() << endl;
    //cout << "Percent On: " << metrics[PERCENT_ON].to_string() << endl;
}

void MajorityRule::transition(){
    BinaryRuleTable::transition();
}

//only looks for B_STATE
void MajorityRule::apply_rule(std::string& vert_label){
    //Implemented in derived classes
}
