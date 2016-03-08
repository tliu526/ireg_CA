/*
Implementation of MajorityRule.

(c) 2016 Tony Liu.
*/

#include "MajorityRule.h"

using namespace std;

const string MajorityRule::CORRECT_CLASS = "CorrectClass";

MajorityRule::MajorityRule(Graph<string, Cell>* graph, Stencil* stencil, int percent_on, float s, int n) 
    : BinaryRuleTable(graph, stencil, percent_on, s) {
        noise = n;
        gen.seed(s);
    }

void MajorityRule::initialize() {
    BinaryRuleTable::initialize();

    //initialize metrics 
    Property correct_class(CORRECT_CLASS, false);
    metrics[CORRECT_CLASS] = correct_class;

    int on_count = get_on_count();
    //Turn one more cell on
    if ((num_cells - on_count) == on_count) {
        
        vector<string> vert_labels = graph->get_vert_labels();

        Property p;
        for(size_t i = 0; i < vert_labels.size(); i++) {
            string label = vert_labels[i];

            p = graph->get_data(label)->get_property(GridGenerator::B_STATE);
            if (!p.b) {
                p.set_bool(true);
                break;
            }            

            Cell *c = graph->get_data(label);
            c->add_property(p);
        }
    }

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

void MajorityRule::apply_noise() {
    if(noise > 0){
        uniform_int_distribution<int> rand_int(0,100);

        vector<string> labels = graph->get_vert_labels();
        for(size_t i = 0; i < labels.size(); i++){
            if(rand_int(gen) < noise){
                Property p = graph->get_data(labels[i])->get_property(GridGenerator::B_STATE);
                p.set_bool(!p.b);
                state_map[labels[i]] = p;
            }
        }    

        update_graph();     
    }
}

void MajorityRule::transition(){
    BinaryRuleTable::transition();

    int tot_on = get_on_count();
    int tot_cells = graph->get_vert_labels().size();
    if((tot_on > 0) && (tot_on < tot_cells)){
        apply_noise();
    }
}

//only looks for B_STATE
void MajorityRule::apply_rule(std::string& vert_label){
    //Implemented in derived classes
}
