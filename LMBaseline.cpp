/*
Runs a replication of the Baseline local majority experiment presented by Messinger et al.
(me07).

Relevant Parameters:
- 15 by 15 grid (225 cells)
- Increments of 1 percent from 1:99 on/off ratio to 99:1
- Maximum of 450 time steps
- Only concerned with completely correct classification
- 1000 randomly assigned initial network configurations for each initial ratio

(c) 2016 Tony Liu
*/

#include "Simulator.h"
#include "SimpleMajorityRule.h"
#include "DelaunayGridGenerator.h"

#include <fstream>

using namespace std;

static const int NUM_STEPS = 250;
static const int NUM_GRID_CONFIGS = 10;
static const int NUM_STATE_CONFIGS = 10;

int main(void){
    string f = "LM_baseline2.csv";

    //TODO no hardcoding
    fstream file;
    file.open(f, fstream::in | fstream::out | fstream::app);
    file << "Correct_Class" << " " << "Initial_Percent" << " " << "Percent_On" << " " << "Time" << endl;
    file.close();

    //iterate through different grid configurations, i is seed
    for(int i = 0; i < NUM_GRID_CONFIGS; i++){
        vector<Point> pts = generate_poisson_disk(15, 15, 30, 0.75, i);
        DelaunayGridGenerator gen(pts, 0, 15, 0, 15);

        //iterate through starting ratios 1:99 to 99:1
        for(int j = 1; j < 100; j++){

            //iterate through different initial state configurations, k is seed
            for(int k = 0; k < NUM_STATE_CONFIGS; k++){
                SimpleMajorityRule rule(gen.get_graph(), float(j)/float(100), k);
                Simulator s(&gen, &rule, NUM_STEPS, f);
                s.simulate();
            }
        }
    }


    return 0;
}