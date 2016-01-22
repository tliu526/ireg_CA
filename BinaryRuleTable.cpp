/**
Implementation of BinaryRuleTable.

(c) 2016 Tony Liu.
*/

#include "BinaryRuleTable.h"
#include "DistComp.h"

#include <algorithm>

const string BinaryRuleTable::PERCENT_ON = "PercentOn";
const string BinaryRuleTable::INIT_PERCENT = "InitPercent";

using namespace std;

BinaryRuleTable::BinaryRuleTable(Graph<string,Cell>* graph, Stencil* stencil, int init_percent, float s, float s_radius) : 
  RuleTable(graph, stencil) 
{
    init_percent_int = init_percent;
    init_percent_on = float(init_percent) / float(100);
    seed = s;
    type = OTHER;
    radius = -1;
    init_radius = s_radius;
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

        //if an initialization radius is provided, find valid points
        if (init_radius > 0){
            Point origin(0,0);

            //lambda comparator function
            sort(vert_labels.begin(), vert_labels.end(), [&](const string& s1, const string& s2){
                    Point orig(0,0);
                    DistComp comp(orig);

//                    cout << "test" << endl;
                    Point p1 =  graph->get_data(s1)->get_point();           
                    Point p2 =  graph->get_data(s2)->get_point();           

//                    cout << "Point 1: " << p1 << endl;
//                    cout << "Point 2: " << p2 << endl;
                    return comp(p1, p2);
            });
            
            int index = 0;
            Point p;

            do { p = graph->get_data(vert_labels[index++])->get_point(); }
            while(pt_in_circle(origin, p, init_radius));

            cout << "Index length " << index << endl;
            vert_labels.erase(vert_labels.begin() + index, vert_labels.end());
        }

        int num_on = int(init_percent_on * vert_labels.size());

        //randomize vector with seeded random number generator
        shuffle(vert_labels.begin(), vert_labels.end(), gen);

        for(size_t i = 0; i < vert_labels.size(); i++) {
            bool state = i < size_t(num_on);

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
