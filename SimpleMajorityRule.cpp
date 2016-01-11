/*
Implementation of SimpleMajorityRule.

(c) 2016 Tony Liu.
*/

#include "SimpleMajorityRule.h"

#include <algorithm>

using namespace std;

const string SimpleMajorityRule::CORRECT_CLASS = "CorrectClass";
const string SimpleMajorityRule::PERCENT_ON = "PercentOn";
const string SimpleMajorityRule::INIT_PERCENT = "InitPercent";

SimpleMajorityRule::SimpleMajorityRule(Graph<string, Cell>* graph, float percent_on, float s) 
    : RuleTable(graph)
{

    init_percent_on = percent_on;
    seed = s;
    type = OTHER;
    radius = -1;
}

void SimpleMajorityRule::initialize() {
    RuleTable::initialize();

    //initialize metrics 
    Property correct_class(CORRECT_CLASS, false);
    Property percent_on(PERCENT_ON, float(0.0));
    Property init_percent(INIT_PERCENT, int(init_percent_on*100));

    metrics[INIT_PERCENT] = init_percent;
    metrics[CORRECT_CLASS] = correct_class;
    metrics[PERCENT_ON] = percent_on;

    //initialize cell state
    default_random_engine gen;
    gen.seed(seed);
    //uniform_real_distribution<float> unif_distr(0,1);

    vector<string> vert_labels = graph->get_vert_labels();

    int num_on = int(init_percent_on * vert_labels.size());

    //randomize vector with seeded random number generator
    shuffle(vert_labels.begin(), vert_labels.end(), gen);

    for(size_t i = 0; i < vert_labels.size(); i++) {
        bool state = i < num_on;

        Property p("State", state);

        Cell *c = graph->get_data(vert_labels[i]);
        c->add_property(p);
    }

    num_cells = vert_labels.size();

    target_class = (float(get_on_count()) / float(num_cells)) > 0.5;
}

int SimpleMajorityRule::get_on_count() {
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
    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        apply_rule(labels[i]);
    }

    //cout << "Number of on cells:" << " " << get_on_count() << endl;

    update_graph();
}

//only looks for B_STATE
void SimpleMajorityRule::apply_rule(std::string& vert_label){
    vector<string>* neighbors = stencil.get_neighbors(vert_label);
    Property p;

    int count = 0;
    int neighborhood_size = neighbors->size() + 1;
    bool cell_state = graph->get_data(vert_label)->get_property(B_STATE).b;

    if (cell_state) count++;

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

size_t SimpleMajorityRule::get_grid_state(){
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