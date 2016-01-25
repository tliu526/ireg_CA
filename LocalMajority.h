/**
An experiment template for running simple local majority experiments.

(c) 2016 Tony Liu.
*/

#ifndef LOCALMAJORITY_H
#define LOCALMAJORITY_H

#include "Experiment.h"
#include "SimpleMajorityRule.h"

class LocalMajority : public Experiment {
    public:
        LocalMajority(string in, string out, int configs, int steps) 
        : grid_file(in), output(out), num_configs(configs), num_steps(steps) {};

        void run() {
            bool header = true;
            GridGenerator gen(grid_file);
            Stencil stencil(gen.get_graph());

            //iterate through starting ratios
            for(int init_percent = 1; init_percent < 100; init_percent++){
                for(int seed = 1; seed <= num_configs; seed++){
                    SimpleMajorityRule rule(gen.get_graph(), &stencil, init_percent, seed);
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
};

#endif