/**
Implementation of BinaryRuleTable.

(c) 2016 Tony Liu.
*/

#include "BinaryRuleTable.h"

#include <algorithm>

const string BinaryRuleTable::PERCENT_ON = "PercentOn";
const string BinaryRuleTable::INIT_PERCENT = "InitPercent";

using namespace std;

BinaryRuleTable::BinaryRuleTable(Graph<string,Cell>* graph, Stencil* stencil, int init_percent, float s) : 
  RuleTable(graph, stencil) 
{
    init_percent_int = init_percent;
    init_percent_on = float(init_percent) / float(100);
    seed = s;
    type = OTHER;
    radius = -1;
}

int BinaryRuleTable::get_on_count() {
    vector<string> labels = graph->get_vert_labels();
    int on_cells = 0;
    for(size_t i = 0; i < labels.size(); i++){
        Property p = graph->get_data(labels[i])->get_property(GridGenerator::B_STATE);
        
        if(p.get_type() == Property::BOOL) {
            if (p.b){
                on_cells++;
            }
        }
        else {
            cout << "Invalid State type" << endl;
            return -1;
        }
    }

    return on_cells;
}

int BinaryRuleTable::get_on_count(string& s){
    vector<string>* neighbors = stencil->get_neighbors(s);
    int count;
    Property p;

    for(size_t i = 0; i < neighbors->size(); i++){
        p = graph->get_data((*neighbors)[i])->get_property(GridGenerator::B_STATE);
        
        if(p.get_type() == Property::BOOL){
            if(p.b){
                count++;
            }            
        }
        else {
            cout << "Invalid State type" << endl;
            return -1;
        }
    }

    return count;
}

size_t BinaryRuleTable::get_grid_state(){
    //TODO optimize get_vert_labels() and ensure consistency
    vector<string> vert_labels = graph->get_vert_labels();

    vector<bool> b_vec;

    for (size_t i = 0; i < vert_labels.size(); i++){
        Property p = graph->get_data(vert_labels[i])->get_property(GridGenerator::B_STATE);
        if(p.get_type() == Property::BOOL){
            b_vec.push_back(p.b);
        }
    }

    hash<vector<bool>> hash_fn;

    return hash_fn(b_vec);
}

void BinaryRuleTable::initialize() {
    RuleTable::initialize();

    //initialize metrics 
    Property percent_on(BinaryRuleTable::PERCENT_ON, float(0.0));
    Property init_percent(BinaryRuleTable::INIT_PERCENT, init_percent_int);

    metrics[BinaryRuleTable::INIT_PERCENT] = init_percent;
    metrics[BinaryRuleTable::PERCENT_ON] = percent_on;

    //initialize cell state, only if seed has been provided
    if(seed > 0){
        default_random_engine gen;
        gen.seed(seed);

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
    }
}

void BinaryRuleTable::transition() {
    vector<string> labels = graph->get_vert_labels();

    for(size_t i = 0; i < labels.size(); i++){
        apply_rule(labels[i]);
    }

    //cout << "Number of on cells:" << " " << get_on_count() << endl;

    update_graph();
}


void BinaryRuleTable::compute_metrics() {}
void BinaryRuleTable::apply_rule(string& l) {}
