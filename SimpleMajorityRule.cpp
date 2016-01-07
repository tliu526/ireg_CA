/*
Implementation of SimpleMajorityRule.

(c) 2016 Tony Liu.
*/

#include "SimpleMajorityRule.h"

using namespace std;

const string SimpleMajorityRule::CORRECT_CLASS = "CorrectClass";
const string SimpleMajorityRule::PERCENT_ON = "PercentOn";

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

    metrics[CORRECT_CLASS] = correct_class;
    metrics[PERCENT_ON] = percent_on;

    //initialize cell state
    default_random_engine gen;
    gen.seed(seed);
    uniform_real_distribution<float> unif_distr(0,1);

    vector<string> vert_labels = graph->get_vert_labels();

    for(size_t i = 0; i < vert_labels.size(); i++) {
        bool state = (unif_distr(gen) < init_percent_on);
        Property p("State", state);

        Cell *c = graph->get_data(vert_labels[i]);
        c->add_property(p);
    }

    num_cells = vert_labels.size();

    if (float(get_on_count()) / float(num_cells) > 0.5){
        target_class = true;
    }
    else {
        target_class = false;
    }
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
    if(percentage > 0.5){
        //currently have majority of ON cells
        metrics[CORRECT_CLASS].set_bool(target_class);    
    }
    else {
        //currently have majority of OFF cells
        metrics[CORRECT_CLASS].set_bool(!target_class);
    }

    metrics[PERCENT_ON].set_float(percentage);
}

void SimpleMajorityRule::transition(){
    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        apply_rule(labels[i]);
    }

    cout << "Number of on cells:" << " " << get_on_count() << endl;

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

    //change to majority value of its neighbors
    if (count > (neighbors->size()/2)) {
        p.set_bool(true);
    }

    else {
        p.set_bool(false);
    }

    state_map[vert_label] = p;
}

bitset SimpleMajorityRule::get_grid_state(){
    //TODO optimize get_vert_labels() and ensure consistency
    vector<string> vert_labels = graph->get_vert_labels();

    bitset<vert_labels.size()> b_set;

    for (size_t i = 0; i < vert_labels.size(); i++){
        Property p = graph->get_data()->get_property(B_STATE);
        if(p.get_type() == Property::BOOL){
            bitset[i] = p.b;
        }
    }

    return b_set;
}