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
#include "VertStencil.h"

#include <fstream>

using namespace std;

static const int NUM_STEPS = 500;
static const int NUM_GRID_CONFIGS = 1;
static const int NUM_STATE_CONFIGS = 100;
static const int SMALL = 25;
static const int MED = 45;
static const int LARGE = 70;

/*
int main(void){

    string f = "penrose_life_vert";
    bool header = true;

    GridGenerator gen("penrose.txt");
    VertStencil vs(gen.get_graph(), &gen);
    //iterate through starting ratios 1:99 to 99:1
    for(int j = 1; j < 100; j++){
    //iterate through different initial state configurations, k is seed
        for(int k = 1; k <= NUM_STATE_CONFIGS; k++){
            SimpleLifeRule rule(gen.get_graph(), &vs, j, k);
            Simulator s(&gen, &rule, NUM_STEPS, f);

            if(header){
                s.metric_headers();
                header = false;
            }
            s.simulate();
        }
    }
    return 0;


/*
    GridGenerator gen("penrose_bat.txt");
    VertStencil vs(gen.get_graph(), &gen);
    SimpleLifeRule rule(gen.get_graph(), &vs, 0);
    Simulator s(&gen, &rule, NUM_STEPS, f, 1);
    s.metric_headers();
    s.simulate();
    gen.graph_to_dot("test");

        */
/*
    string f = "life_oscillator";
    bool header = true;

    vector<Point> pts = generate_poisson_disk(SMALL, SMALL, 30, 0.75, 1);
    DelaunayGridGenerator gen(pts, 0, SMALL, 0, SMALL);
    SimpleLifeRule rule(gen.get_graph(), 54, 1);
    Simulator s(&gen, &rule, NUM_STEPS, f, 1);
    s.metric_headers();
    s.simulate();
    return 0;

    //iterate through different grid configurations, i is seed
    for(int i = 0; i < NUM_GRID_CONFIGS; i++){
        vector<Point> pts = generate_poisson_disk(SMALL, SMALL, 30, 0.75, i);
        DelaunayGridGenerator gen(pts, 0, SMALL, 0, SMALL);

        //iterate through starting ratios 1:99 to 99:1
        for(int j = 1; j < 100; j++){
        //iterate through different initial state configurations, k is seed
            for(int k = 0; k < NUM_STATE_CONFIGS; k++){
                SimpleLifeRule rule(gen.get_graph(), j, k);
                Simulator s(&gen, &rule, NUM_STEPS, f);
                
                if(header){
                    s.metric_headers();
                    header = false;
                }
                s.simulate();
            }
        }
    }

   return 0;

}
*/