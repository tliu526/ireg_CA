/**
An experiment template for running lambda experiments.

Valid experiment flags:
-subregion
-starting configurations (trials)
-time 

TODO:
-add option to set number of neighbors or number of states

(c) 2016 Tony Liu.
*/

#ifndef LAMBDAEXPR_H
#define LAMBDAEXPR_H

#include "Experiment.h"
#include "LambdaRule.h"

using namespace std;

class LambdaExpr : public Experiment {
    public:
        LambdaExpr(string in, string out, int configs, int steps, int sd, float r = 0, int n_states = 8, bool step = true)
        : grid_file(in), output(out), num_configs(configs), num_steps(steps), start_seed(sd), init_radius(r), step_through(step), num_states(n_states) {};

        void run(){
            int NUM_NEIGHBORS = 4;

            for(int seed = start_seed; seed < (start_seed + num_configs); seed++){
                string name = output + "_" + to_string(seed);
                GridGenerator gen(grid_file);

                Stencil stencil(gen.get_graph());
                LambdaRule rule(gen.get_graph(), &stencil, NUM_NEIGHBORS, num_states, seed, init_radius);

                //ugly way to initialize headers
                Simulator s(&gen, &rule, num_steps, name);
                s.metric_headers();

                for(int i = 0; i <= rule.get_max_lambda(); i++) {
                    Simulator s(&gen, &rule, num_steps, name, 0, 1);
                    s.simulate();
                    if(step_through) rule.increment_lambda();
                    else rule.set_lambda(i);
                }
            }
        }

    protected:
        //the input gridname
        string grid_file;
        //the output filename
        string output;

        //the initial seed starting value
        int start_seed;

        //the number of initial starting configurations
        int num_configs;

        //the maximum number of timesteps to run for
        int num_steps;

        //the number of states
        int num_states;

        //the subregion radius for initialization
        float init_radius;

        //determines whether lambda is changed via step-through or by random table
        bool step_through;
};

#endif