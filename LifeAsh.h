/**
An experiment template for running life ash experiments. This template only takes metrics
and grid snapshots at the end of a simulation run.

(c) 2016 Tony Liu.
*/
#ifndef LIFEASH_H
#define LIFEASH_H

#include "Experiment.h"
#include "VertStencil.h"
#include "SimpleLifeRule.h"

using namespace std;

class LifeAsh : public Experiment {
    public:
        LifeAsh(string in, string out, int configs, int steps, float r = 0) 
        : grid_file(in), output(out), num_configs(configs), num_steps(steps), init_radius(r) {};

        void run() {
            bool header = true;
            //initialize generator and stencil
            GridGenerator gen(grid_file);
            VertStencil vs(gen.get_graph(), &gen);

            //iterate through starting ratios
            for(int init_percent = 1; init_percent < 100; init_percent++){
                for(int seed = 1; seed <= num_configs; seed++){
                    SimpleLifeRule rule(gen.get_graph(), &vs, init_percent, seed, init_radius);
                    Simulator s(&gen, &rule, num_steps, output);

                    if(header){
                        s.metric_headers();
                        header = false;
                    }
                    s.simulate();
                }
            }
        }

    protected:
        //the input gridname
        string grid_file;
        //the output filename
        string output;

        //the number of initial starting configurations
        int num_configs;

        //the maximum number of timesteps to run for
        int num_steps;

        float init_radius;
};

#endif