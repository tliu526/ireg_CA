/**
A wrapper for experiments to be queued up.

TODO think about what particular parameters may be needed.

(c) 2016 Tony Liu.
*/
#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "GridGenerator.h"
#include "Simulator.h"
#include "Stencil.h"
#include "RuleTable.h"

class Experiment {
    public:
        Experiment() {};

        //the experiment body will be placed here
        virtual void run() {};
};

#endif