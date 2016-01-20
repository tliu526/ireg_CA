/**
An experiment template for metrics on the connectivity of a particular grid layout.

(c) 2016 Tony Liu.
*/

#ifndef CONNECTIVITYEXPR_H
#define CONNECTIVITYEXPR_H

#include "Experiment.h"

using namespace std;

class ConnectivityExpr : public Experiment {
    public:
        ConnectivityExpr(string in, string out, Stencil* sten)
        : grid_file(in), output(out), stencil(sten){};

        void run() {
            GridGenerator gen(grid_file);
            
        }

    protected:
        string grid_file;
        string output;
        Stencil *stencil;
};

#endif