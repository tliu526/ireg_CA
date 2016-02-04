/**
Implementation of the LambdaRule.

(c) 2016 Tony Liu.
*/

#include "LambdaRule.h"

//for debugging
#include "VNStencil.h"
#include "RegularGridGenerator.h"

#include <string>

using namespace std;

const string LambdaRule::LAMBDA = "Lambda";
const string LambdaRule::FREQUENCY = "Freq";


LambdaRule::LambdaRule(Graph<std::string,Cell>* graph, Stencil* stencil, int n_neighbors, int n_states, int s) : RuleTable(graph, stencil) {
  num_neighbors = n_neighbors;
  num_states = n_states;
  seed = s;
}

void LambdaRule::initialize() {
    RuleTable::initialize();

    num_bits = count_bits(num_states-1);

    bit_rule.resize( ( (1 << ((num_neighbors+1)* num_bits)) * num_bits), false);

    q_state = 0; //quiescent state is 0 unless otherwise noted in derived classes
    lambda = 0; //start out with everything mapped to the quiescent state

    //initialize metrics 
    Property lambda_prop(LambdaRule::LAMBDA, lambda);

    metrics[LAMBDA] = lambda_prop;

    for(size_t state = 0; state < num_states; state++){
        string f_label = FREQUENCY + to_string(state);
        Property freq_count(f_label, 0); //TODO is frequency a float or int?

        metrics[f_label] = freq_count;
    }

    //random initial configuration
    if(seed > 0){
        default_random_engine gen;
        gen.seed(seed);
        
        //range from 0 to num_states-1
        uniform_int_distribution<int> s_distr(0, num_states-1);

        vector<string> vert_labels = graph->get_vert_labels();
        for (size_t i = 0; i < vert_labels.size(); i++){
            int state = s_distr(gen);

            Property p("State", state);

            Cell *c = graph->get_data(vert_labels[i]);
            c->add_property(p);
        }
    }
}

void LambdaRule::transition() {
    RuleTable::transition();
}

void LambdaRule::compute_metrics() {
    RuleTable::compute_metrics();

    metrics[LAMBDA].set_int(lambda);
    //TODO frequency 
}

void LambdaRule::apply_rule(string &label) {
    int s_index = get_bit_rule_index(label);

    cout << "State index: " << s_index << endl;

    Property p = graph->get_data(label)->get_property(GridGenerator::I_STATE);

    int state = get_bit_rule_state(s_index);

    cout << "Next state: " << state << endl;    

    p.set_int(state);
    state_map[label] = p;
}

int LambdaRule::get_bit_rule_state(int index) {
    string bit_str = "";
    for (size_t i = index; i < (index + num_bits); i++){
        bit_str += to_string(bit_rule[i]);
    }

    return stoi(bit_str, 0, 2);
}

int LambdaRule::get_bit_rule_index(string &label) {
    Property p;
    string bit_str = "";
    vector<string>* neighbors = stencil->get_neighbors(label);

    //append neighbors
    for(size_t i = 0; i < neighbors->size(); i++){
        p = graph->get_data((*neighbors)[i])->get_property(GridGenerator::I_STATE);

        if(p.get_type() == Property::INT){
            bit_str += get_bit_str(p.i);
        }
        else {
            cout << "Invalid State type" << endl;
            return -1;
        }
    }

    p = graph->get_data(label)->get_property(GridGenerator::I_STATE);
    bit_str += get_bit_str(p.i);

    //base 2
    return stoi(bit_str, 0, 2);
}

size_t LambdaRule::get_grid_state() {
    //TODO optimize get_vert_labels() and ensure consistency
    vector<string> vert_labels = graph->get_vert_labels();

    string state = "";

    for (size_t i = 0; i < vert_labels.size(); i++){
        Property p = graph->get_data(vert_labels[i])->get_property(GridGenerator::I_STATE);
        if(p.get_type() == Property::INT){
            state += to_string(p.i);
        }
    }

    hash<string> hash_fn;

    return hash_fn(state);
}

void LambdaRule::set_lambda(int l) {
    //TODO
}

int LambdaRule::increment_lambda() {
    //TODO
}

int main() {
    RegularGridGenerator gen(0, 64, 0, 64, true);
    Stencil stencil(gen.get_graph());

    LambdaRule rule(gen.get_graph(), &stencil, 4, 8, 5);

    cout << "rule bit size: " << ((1 << (5 * 3)) * 3) << endl;
    rule.initialize();
    rule.transition();
}
