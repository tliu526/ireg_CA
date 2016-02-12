/**
Implementation of LambdaRule.

(c) 2016 Tony Liu.
*/

#include "LambdaRule.h"

//for debugging
#include "VNStencil.h"
#include "RegularGridGenerator.h"
#include "Simulator.h"
#include "DistComp.h"

#include <string>
#include <cmath>

using namespace std;

const string LambdaRule::LAMBDA = "Lambda";
const string LambdaRule::FREQUENCY = "Freq";


LambdaRule::LambdaRule(Graph<std::string,Cell>* graph, Stencil* stencil, int n_neighbors, int n_states, int s, float s_radius) : RuleTable(graph, stencil) {
    num_neighbors = n_neighbors;
    num_states = n_states;
    seed = s;
    sub_radius = s_radius;

    while(q_str.size() < num_neighbors){
        q_str += "0";
    }

    num_bits = count_bits(num_states-1);

    bit_rule.resize( ( (1 << ((num_neighbors+1)* num_bits)) * num_bits), false);

    q_state = 0; //quiescent state is 0 unless otherwise noted in derived classes
    lambda = 0; //start out with everything mapped to the quiescent state
    nonq_count = 0;


    init_transition_table();

    //sets up transition keys to modify
    typename map<string, int>::iterator map_it;
    for(map_it = trans_table.begin(); map_it != trans_table.end(); map_it++){
        string key = map_it->first;
        if(key.find(q_str) == string::npos){
            trans_keys.push_back(key);
        }
    }

    //initialize seed
    gen.seed(seed);    

    shuffle(trans_keys.begin(), trans_keys.end(), gen);
    key_it = trans_keys.begin();
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
    //range from 0 to num_states-1
    uniform_int_distribution<int> s_distr(0, num_states-1);

    vector<string> vert_labels = graph->get_vert_labels();

    int sub_index = vert_labels.size();

    if (sub_radius > 0){
        sub_index = 0;
        Point origin(0,0);

        //lambda comparator function
        sort(vert_labels.begin(), vert_labels.end(), [&](const string& s1, const string& s2){
            Point orig(0,0);
            DistComp comp(orig);

            Point p1 =  graph->get_data(s1)->get_point();           
            Point p2 =  graph->get_data(s2)->get_point();           
            return comp(p1, p2);
        });

        Point p;
        do { p = graph->get_data(vert_labels[sub_index++])->get_point(); }
        while((sub_index < vert_labels.size()) && pt_in_circle(origin, p, sub_radius));

        subregion_labels = vector<string>(vert_labels.begin(), vert_labels.begin()+sub_index);
    }

    for (size_t i = 0; i < vert_labels.size(); i++){
        int state = 0;
        //only change if within radius
        if(i < sub_index) {
            state = s_distr(gen);
        }

        Property p("State", state);

        Cell *c = graph->get_data(vert_labels[i]);
        c->add_property(p);
    }

}

void LambdaRule::init_transition_table() {
    string cur_str;
    string table_key;

    vector<string> min_rot_nbrs; //tracks the minimal rotation neighborhoods
    //iterate over all possible neighborhood values
    for (int i = 0; i < int(pow(num_states, num_neighbors)); i++){        
        cur_str = str_change_base(i, num_states);
        
        while(cur_str.size() < num_neighbors){
            cur_str = "0" + cur_str;
        }

        cur_str = min_rotation(cur_str);

        if(count(min_rot_nbrs.begin(), min_rot_nbrs.end(), cur_str) == 0){
            min_rot_nbrs.push_back(cur_str);
            //cout << cur_str << endl;
            //insert into trans_table, init to 0
            for(int center = 0; center < num_states; center++){
                table_key = cur_str + to_string(center);
                trans_table[table_key] = 0;
            }
        }
    }

    cout << "Number of unique rotations: " << min_rot_nbrs.size() << endl;
}

string LambdaRule::min_rotation(string& in) {
    string best = in;
    string start = in;

    do {
        rotate(in.begin(), in.begin()+1, in.end());
        if(in < best){
            best = in;
        }
    }
    while(start != in);

    return best;
}

void LambdaRule::transition() {
    RuleTable::transition();
    //compute_freq();
}

void LambdaRule::compute_metrics() {
    RuleTable::compute_metrics();

    metrics[LAMBDA].set_int(lambda);

    compute_freq();
    
    for(int i = 0; i < num_states; i++) {
        string label = FREQUENCY + to_string(i);
        metrics[label].set_int(state_counts[i]);
    }
}

void LambdaRule::compute_freq() {
    state_counts.clear();    
    

    vector<string> labels;

    if(sub_radius > 0){
        labels = subregion_labels;
    }
    else {
        labels = graph->get_vert_labels();
    }

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

string LambdaRule::get_trans_key(string &label) {
    Property p;
    string out_str;

    vector<string>* neighbors = stencil->get_neighbors(label);
    
    for(size_t i=0; i < neighbors->size(); i++){
        p = graph->get_data((*neighbors)[i])->get_property(GridGenerator::I_STATE);

        if(p.get_type() == Property::INT){
            out_str += to_string(p.i);
        }
    }

    out_str = min_rotation(out_str);
    //append center state
    p = graph->get_data(label)->get_property(GridGenerator::I_STATE);

    if(p.get_type() == Property::INT){
        out_str += to_string(p.i);
    }

    return out_str;
}

void LambdaRule::apply_rule(string &label) {
    Property p = graph->get_data(label)->get_property(GridGenerator::I_STATE);

    int state = trans_table[get_trans_key(label)];
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

float LambdaRule::get_max_lambda() {
    return 1.0 - float(1)/float(num_states);
}

int LambdaRule::increment_lambda() {
    
    if(lambda > 100) {
        cout << "lambda cannot be incremented further" << endl;
        return -1;
    }

    int on_count; //the number of non quiescent states needed to increment lambda  
    lambda += 1;
    on_count = int(trans_keys.size()*(float(lambda)/float(100)));

//    cout << "On count for lambda: " << on_count << endl;

    //non quiescent states
    uniform_int_distribution<int> state_distr(1, num_states-1);

    while(nonq_count < on_count) {
        string key = *key_it;
        if(trans_table[key] == q_state){
            trans_table[key] = state_distr(gen);
            nonq_count++;
        }
        key_it++;
    }

    return lambda;
}

int main(int argc, char**argv) {
    if(argc < 3){
        cout << "Provide a begin and end seed" << endl;
        return -1;
    }

    int begin = atoi(argv[1]);
    int end = atoi(argv[2]);

    cout << "Begin seed: " << begin << endl;
    cout << "End seed: " << end << endl;

    for(int seed = begin; seed <= end; seed++){

        string name = "subregion_entropy_" + to_string(seed);
        RegularGridGenerator gen(-64, 64, -64, 64, true);
        Stencil stencil(gen.get_graph());
        LambdaRule rule(gen.get_graph(), &stencil, 4, 8, seed, 40);

        Simulator s(&gen, &rule, 500, name);
        s.metric_headers();

        for(int i = 0; i <= int(rule.get_max_lambda()*100); i++) {
            Simulator s(&gen, &rule, 500, name, 0, 1);
            s.simulate();
            rule.increment_lambda();
        }
    }
}
