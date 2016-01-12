/*
Implementation of SimpleMajorityRule.

(c) 2016 Tony Liu.
*/

#include "SimpleMajorityRule.h"

using namespace std;

const string SimpleMajorityRule::CORRECT_CLASS = "CorrectClass";

SimpleMajorityRule::SimpleMajorityRule(Graph<string, Cell>* graph, float percent_on, float s) 
    : BinaryRuleTable(graph, percent_on, s) {}

void SimpleMajorityRule::initialize() {
    BinaryRuleTable::initialize();

    //initialize metrics 
    Property correct_class(CORRECT_CLASS, false);
    metrics[CORRECT_CLASS] = correct_class;

    target_class = (float(get_on_count()) / float(num_cells)) > 0.5;
}

void SimpleMajorityRule::compute_metrics() {
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

void SimpleMajorityRule::transition(){
    BinaryRuleTable::transition();
}

//only looks for B_STATE
void SimpleMajorityRule::apply_rule(std::string& vert_label){
    vector<string>* neighbors = stencil.get_neighbors(vert_label);
    Property p;

    int count = get_on_count(vert_label);
    int neighborhood_size = neighbors->size() + 1;
    bool cell_state = graph->get_data(vert_label)->get_property(B_STATE).b;

    if (cell_state) count++;
/*
    for(size_t i = 0; i < neighbors->size(); i++){
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
*/
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
