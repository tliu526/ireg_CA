/**
Implementation of LambdaRule.

(c) 2016 Tony Liu.
*/

#include "LambdaRule.h"

//for debugging
#include "VNStencil.h"
#include "RegularGridGenerator.h"
#include "Simulator.h"

#include <string>
#include <cmath>

using namespace std;

const string LambdaRule::LAMBDA = "Lambda";
const string LambdaRule::FREQUENCY = "Freq";


LambdaRule::LambdaRule(Graph<std::string,Cell>* graph, Stencil* stencil, int n_neighbors, int n_states, int s) : RuleTable(graph, stencil) {
  num_neighbors = n_neighbors;
  num_states = n_states;
  seed = s;

  num_bits = count_bits(num_states-1);
  
  bit_rule.resize( ( (1 << ((num_neighbors+1)* num_bits)) * num_bits), false);
  
  q_state = 0; //quiescent state is 0 unless otherwise noted in derived classes
  lambda = 0; //start out with everything mapped to the quiescent state
  nonq_count = 0;
}

void LambdaRule::initialize() {
    RuleTable::initialize();

    state_counts.clear();

    //initialize metrics 
    Property lambda_prop(LambdaRule::LAMBDA, lambda);

    metrics[LAMBDA] = lambda_prop;

    for(size_t state = 0; state < num_states; state++){
        string f_label = FREQUENCY + to_string(state);
        Property freq_count(f_label, int(0)); 

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

    compute_freq();
}

void LambdaRule::compute_metrics() {
    RuleTable::compute_metrics();

    metrics[LAMBDA].set_int(lambda);

    //compute_freq();
    
    for(int i = 0; i < num_states; i++) {
        string label = FREQUENCY + to_string(i);
        metrics[label].set_int(state_counts[i]);
    }
}

void LambdaRule::compute_freq() {
    //state_counts.clear();
   
    vector<string> labels = graph->get_vert_labels();
    
    for(size_t i = 0; i < labels.size(); i++) {
        Property p = graph->get_data(labels[i])->get_property(GridGenerator::I_STATE);
        if(p.get_type() == Property::INT) {
            if(state_counts.count(p.i) == 0) {
                state_counts[p.i] = 0;
            }
            state_counts[p.i] += 1;
        }        
    }
    
}

void LambdaRule::apply_rule(string &label) {
    int s_index = get_bit_rule_index(label);

    Property p = graph->get_data(label)->get_property(GridGenerator::I_STATE);

    int state = get_bit_rule_state(s_index);

    p.set_int(state);
    state_map[label] = p;
}

int LambdaRule::get_bit_rule_state(int index) {
    string bit_str = "";
    
    index *= num_bits;
    
    for (size_t i = index; i < (index + num_bits); i++){
        bit_str += to_string(bit_rule[i]);
    }

    return stoi(bit_str, 0, 2);
}

void LambdaRule::set_bit_rule_state(int index, int state) {
    if(state >= num_states) {
        cout << "Invalid state" << endl;
        return;
    } 
  
    index *= num_bits;

    for (int i = (index + num_bits-1); i >= index; i--){
        bit_rule[i] = (state & 1);
        state >>= 1;
    }
}


int LambdaRule::get_bit_rule_index(string &label) {
    Property p;
    string bit_str = "";
    vector<string>* neighbors = stencil->get_neighbors(label);

    //append neighbors
    for(size_t i = 0; i < neighbors->size(); i++){
        p = graph->get_data((*neighbors)[i])->get_property(GridGenerator::I_STATE);

        if(p.get_type() == Property::INT){
            if(p.i != 0) {
                bit_str += get_bit_str(p.i);
            }
            else {
                for(size_t i = 0; i < num_bits; i++) {
                    bit_str += "0";
                }
            }
        }
        else {
            cout << "Invalid State type" << endl;
            return -1;
        }
    }

    p = graph->get_data(label)->get_property(GridGenerator::I_STATE);

    if(p.i != 0) {
        bit_str += get_bit_str(p.i);
    }
    else {
        for(size_t i = 0; i < num_bits; i++) {
           bit_str += "0";
        }
    }

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
    if(l > 100 || l < 0) {
        cout << "invalid lambda value" << endl;
        return;
    }
    //TODO
}

int LambdaRule::increment_lambda() {
    
    if(lambda > 100) {
        cout << "lambda cannot be incremented further" << endl;
        return -1;
    }

    int on_count; //the number of non quiescent states needed to increment lambda  
    lambda += 1;
    on_count = int( pow(num_states, num_neighbors+1)*(float(lambda)/float(100)));

    cout << "On count for lambda: " << on_count << endl;

    default_random_engine gen;
    gen.seed(seed);
    
    vector<int> indices;
    for(size_t i = 0; i <= bit_rule.size() / num_bits; i++) {
        indices.push_back(i);
    }
    shuffle(indices.begin(), indices.end(), gen);

    //non quiescent states
    uniform_int_distribution<int> state_distr(1, num_states-1);

    int i = 0;
    while(nonq_count < on_count) {
        if(get_bit_rule_state(i) == q_state) {
            set_bit_rule_state(i, state_distr(gen));
            nonq_count++;
        }   

        i++;
    }

    return lambda;
}

int main() {
    int seed = 100;

    RegularGridGenerator gen(0, 64, 0, 64, true);
    Stencil stencil(gen.get_graph());
    LambdaRule rule(gen.get_graph(), &stencil, 4, 8, seed);

    Simulator s(&gen, &rule, 1000, "lambda_med");
    s.metric_headers();

    for(int i = 0; i < 100; i++) {
      Simulator s(&gen, &rule, 1000, "lambda_med");
      s.simulate();
      rule.increment_lambda();
    }
}
