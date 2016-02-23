/**
An experiment template for running GKL majority experiments.
//TODO run on periodic regular grid
(c) 2016 Tony Liu.
*/

#ifndef GKLMAJORITY_H
#define GKLMAJORITY_H

#include "Experiment.h"
#include "GKLRule.h"
#include "VNStencil.h"

class GKLMajority : public Experiment {
    public:
        GKLMajority(string in, string out, int configs, int steps) 
        : grid_file(in), output(out), num_configs(configs), num_steps(steps) {};

        void run() {
            bool header = true;
            GridGenerator gen(grid_file);
//            Stencil stencil(gen.get_graph());
            VNStencil stencil(gen.get_graph(), &gen);

            //iterate through starting ratios
            for(int init_percent = 1; init_percent < 100; init_percent++){
                for(int seed = 1; seed <= num_configs; seed++){
                    GKLRule rule(gen.get_graph(), &stencil, init_percent, seed);
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