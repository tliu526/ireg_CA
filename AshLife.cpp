/**
Runs a replication of AshLife experiments presented by Hill et al. (hi05).

Relevant Parameters:
- Grid sizes: Small (~25x25), Med (~44x44), Large (~72x72), XLarge (118x118)
- Mean lifetime to Stability experiment: Plot Initial Density (1% to 100%) against Mean Lifetime
- Liftetime to stability against ash density, for initial densities D = 20%, 40%, 60%.

(c) 2016 Tony Liu.
*/

#include "Simulator.h"
#include "SimpleLifeRule.h"
#include "DelaunayGridGenerator.h"

#include <fstream>

using namespace std;

static const int NUM_STEPS = 500;
static const int NUM_GRID_CONFIGS = 5;
static const int NUM_STATE_CONFIGS = 10;
static const int SMALL = 25;
static const int MED = 45;
static const int LARGE = 70;

int main(void){
    string f = "life_test_m.csv";

    fstream file;
    file.open(f, fstream::in | fstream::out | fstream::app);
    file << "Initial_Percent" << " " << "Percent_On" << " " << "Time" << endl;
    file.close();

    //iterate through different grid configurations, i is seed
    for(int i = 0; i < NUM_GRID_CONFIGS; i++){
        vector<Point> pts = generate_poisson_disk(MED, MED, 30, 0.75, i);
        DelaunayGridGenerator gen(pts, 0, MED, 0, MED);

        //iterate through starting ratios 1:99 to 99:1
        for(int j = 1; j < 100; j++){

            //iterate through different initial state configurations, k is seed
	    for(int k = 0; k < NUM_STATE_CONFIGS; k++){
	      SimpleLifeRule rule(gen.get_graph(), int(j), k);
                Simulator s(&gen, &rule, NUM_STEPS, f);
                s.simulate();
            }
        }
    }

    return 0;
}
