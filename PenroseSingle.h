/**
An experiment template for investigating a particular Penrose Life configuration.

(c) 2016 Tony Liu.
*/
#ifndef PENROSESINGLE_H
#define PENROSESINGLE_H

#include "Experiment.h"

class PenroseSingle : public Experiment {
    public:
        PenroseSingle(string in, string out, int init_percent, int seed, int steps) 
        : grid_file(in), output(out), init_percent(init_percent), seed(seed), num_steps(steps) {};

    void run() {
        int snapshot_freq = 1;

        GridGenerator gen(grid_file);
        VertStencil vs(gen.get_graph(), &gen);
        SimpleLifeRule rule(gen.get_graph(), &vs, init_percent, seed);
        Simulator s(&gen, &rule, num_steps, output, snapshot_freq, snapshot_freq);
        s.metric_headers();
        s.simulate();
    }

    protected:
        string grid_file;
        string output;
        int init_percent;
        int num_steps;
        int seed;
};


#endif