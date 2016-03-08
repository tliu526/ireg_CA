/**
An experiment template for running 50-50 simple local majority experiments.
As per me07, we choose initial percentages from a gaussian distribution N(50,6).

(c) 2016 Tony Liu.
*/

#ifndef FFLOCALMAJORITY_H
#define FFLOCALMAJORITY_H

#include "Experiment.h"
#include "SimpleMajorityRule.h"

#include <random>

class FFLocalMajority : public Experiment {
    public:
        FFLocalMajority(string in, string out, int configs, int steps, int n = 0) 
        : grid_file(in), output(out), num_configs(configs), num_steps(steps), noise(n) {};

        void run() {
            bool header = true;
            GridGenerator gen(grid_file);
            Stencil stencil(gen.get_graph());
            default_random_engine rand_gen;
            int init_percent;
            for(int seed = 1; seed <= num_configs; seed++){
                rand_gen.seed(seed);
                normal_distribution<float> gauss(50,6);

                init_percent = int(gauss(rand_gen));
                
                SimpleMajorityRule rule(gen.get_graph(), &stencil, init_percent, seed, noise);
                Simulator s(&gen, &rule, num_steps, output);

                if(header){
                    s.metric_headers();
                    header = false;
                }
                s.simulate();
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

        int noise;
};

#endif