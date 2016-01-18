/**
An experiment for investigating a particularly long-lived Penrose Life configuration.

With seed 1 and initial density of 22%, this run took 173 timesteps to stablize 
with a final ash density of 0.01904.

(c) 2016 Tony Liu.
*/
#ifndef PENROSELIFEVERT22_H
#define PENROSELIFEVERT22_H

#include "Experiment.h"
#include "VertStencil.h"
#include "SimpleLifeRule.h"
#include <string>

class PenroseLifeVert22 : public Experiment {
public:
    void run () {
        int seed = 1;
        int init_percent = 22;
        int num_steps = 500;
        int grid_freq = 1; //how often we take a grid snapshot
        int stat_freq = 1;
        std::string file = "penrose_life_long";

       GridGenerator gen("penrose.txt");
       VertStencil vs(gen.get_graph(), &gen);
       SimpleLifeRule rule(gen.get_graph(), &vs, init_percent, seed);
       Simulator s(&gen, &rule, num_steps, file, grid_freq, stat_freq);
       s.metric_headers();
       s.simulate();
    }
};

#endif