/**
Implementation of RhombGlider.

(c) 2016 Tony Liu.
*/

#include "RhombGlider.h"

//debugging
#include "RegularGridGenerator.h"
#include "VertStencil.h"


//max neighborhood size, TODO think about implications
const int RhombGlider::NUM_NEIGHBORS = 11;
const int RhombGlider::NUM_STATES = 4;

RhombGlider::RhombGlider(Graph<std::string,Cell>* graph, Stencil* stencil, int seed, float s_radius) :
    LambdaRule(graph, stencil, NUM_NEIGHBORS, NUM_STATES, seed, s_radius) {}

void RhombGlider::apply_rule(string& label){
    LambdaRule::apply_rule(label);
}

void RhombGlider::init_transition_table(){
    LambdaRule::init_transition_table();

    //initialize rule table as per go12
    for(map<string, int>::iterator map_it = trans_table.begin(); map_it != trans_table.end(); map_it++){
        string key = map_it->first;
        string nbrhood = key.substr(0, key.length()-1);
        string center = key.substr(key.length()-1);

        cout << "key: " << key << endl;
        cout << "neighborhood: " << nbrhood << endl;
        cout << "center: " << center << endl;
    }
}
/*
int main (int argc, char**argv) {
        RegularGridGenerator gen(0, 10, 0, 10, false);
//        VertStencil stencil(gen.get_graph(), &gen);
        Stencil stencil(gen.get_graph());
        RhombGlider rule(gen.get_graph(), &stencil, 1);
}
*/