/**
Implementation of GKL Rule.

(c) 2016 Tony Liu.
*/

#include "GKLRule.h"

using namespace std;

GKLRule::GKLRule(Graph<std::string,Cell>* graph, Stencil* stencil, int init_percent, float seed) 
  : MajorityRule(graph, stencil, init_percent, seed) {}

void GKLRule::apply_rule(string &label) {
    Property p = graph->get_data(label)->get_property(GridGenerator::B_STATE);
    vector<string>* neighbors = stencil->get_neighbors(label);
    int on_count;
    //the subset of neigbhors to consider, depending on the center state
    vector<string> sub_nbrhood;
    sub_nbrhood.push_back(label);

    //invoke GKL only if there is a correct number of neighbors
    if(neighbors->size() == 4){
        cout << "Invoking GKL" << endl;
        if(p.get_type() == Property::BOOL){
            if(p.b){
                sub_nbrhood.push_back((*neighbors)[0]);
                sub_nbrhood.push_back((*neighbors)[3]);
            }
            else {
                sub_nbrhood.push_back((*neighbors)[1]);
                sub_nbrhood.push_back((*neighbors)[2]);    
            }
            on_count = get_on_count(sub_nbrhood);
            if(on_count >= 2){
              p.set_bool(true);
              state_map[label] = p;        
            }
            else {
              p.set_bool(false);
              state_map[label] = p;                        
            }
        }
        else {
            cout << "Invalid State type" << endl;
            return;
        }
    }
    //else invoke majority rule
    else {
        cout << "Invoking simple majority" << endl;
        on_count = get_on_count(label);
        //change to majority value of its neighbors. If no majority, keep the same state
        if (float(on_count) > (float(neighbors->size())/float(2))) {
            p.set_bool(true);
            state_map[label] = p;
        }
        else if (float(on_count) < (float(neighbors->size())/float(2))){
            p.set_bool(false);
            state_map[label] = p;
        }

    }
}