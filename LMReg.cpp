/**
A reproduction of the LM baseline computation with regular grids.

(c) 2016 Tony Liu.
*/
#include "Simulator.h"
#include "SimpleMajorityRule.h"
#include "RegularGridGenerator.h"

#include <fstream>

using namespace std;

static const int NUM_STEPS = 250;
static const int NUM_STATE_CONFIGS = 50;

int main(void){
//    string f = "test.csv";

    //TODO no hardcoding
    fstream file;
    file.open(f, fstream::in | fstream::out | fstream::app);
    file << "Correct_Class" << " " << "Initial_Percent" << " " << "Percent_On" << " " << "Time" << endl;
    file.close();

    //iterate through starting ratios 1:99 to 99:1
    for(int i = 1; i < 100; i++){
        RegularGridGenerator gen(0, 15, 0, 15,true);

        //iterate through different initial state configurations, k is seed
        for(int j = 0; j < NUM_STATE_CONFIGS; j++){
            SimpleMajorityRule rule(gen.get_graph(), float(i)/float(100), j);
            Simulator s(&gen, &rule, NUM_STEPS, f);
            s.simulate();
        }
    }
    return 0;
}